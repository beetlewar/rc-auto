using Metrics.Host.Dto;
using Microsoft.AspNetCore.Mvc;

namespace Metrics.Host.Controllers
{
    [Route("api/[controller]")]
    public class MetricsController
    {
        private readonly Services.MetricsWriter _metricsWriter;

        public MetricsController(Services.MetricsWriter metricsWriter)
        {
            _metricsWriter = metricsWriter ?? throw new System.ArgumentNullException(nameof(metricsWriter));
        }

        [HttpPost]
        public void HandleMetrics([FromBody] MetricsDto metrics)
        {
            _metricsWriter.AddMetric(metrics);
        }
    }
}
