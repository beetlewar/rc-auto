using System;
using System.Collections.Concurrent;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using Metrics.Host.Dto;
using Microsoft.AspNetCore.Hosting;

namespace Metrics.Host.Services
{
    public class MetricsWriter : IDisposable
    {
        private readonly string _path;
        private readonly ConcurrentQueue<MetricsDto> _metricsQueue = new ConcurrentQueue<MetricsDto>();
        private readonly ManualResetEventSlim _eventMetrics = new ManualResetEventSlim();
        private readonly ManualResetEventSlim _eventDispose = new ManualResetEventSlim();
        private volatile bool _disposing;
        private bool _disposed;

        public MetricsWriter(IHostingEnvironment hostingEnv)
        {
            var fileName = $"metrics_{DateTime.UtcNow:yyyy-MM-dd hh.mm.ss}.csv";

            _path = Path.Combine(hostingEnv.WebRootPath, fileName);
        }

        public void Start()
        {
            Task.Run(() => {
                while (!_disposing)
                {
                    _eventMetrics.Wait();

                    MetricsDto metrics;
                    while (_metricsQueue.TryDequeue(out metrics))
                    {
                        WriteMetrics(metrics);
                    }

                    _eventMetrics.Reset();
                }
                _eventDispose.Set();
            });
        }

        public void AddMetric(MetricsDto metric)
        {
            _metricsQueue.Enqueue(metric);
            _eventMetrics.Set();
        }

        private void WriteMetrics(MetricsDto metrics)
        {
            var contents = $@"""{metrics.Duration}"", ""{metrics.Uri}"", ""{metrics.Content}"", ""{metrics.Code}""{Environment.NewLine}";

            File.AppendAllText(_path, contents);
        }

        public void Dispose()
        {
            if (_disposed)
            {
                return;
            }

            _disposing = true;
            _eventMetrics.Set();
            _eventDispose.Wait(TimeSpan.FromSeconds(30));
            _disposed = true;
        }
    }
}
