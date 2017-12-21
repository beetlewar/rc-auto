#pragma once

struct SerialPortData
{
  private:
    uint8_t *_data;
    uint16_t _size;

  public:
    SerialPortData(uint16_t bufSize)
    {
        _data = new uint8_t[bufSize];
    }

    ~SerialPortData()
    {
        delete[] _data;
    }

    void copyData(uint8_t *source, uint16_t size)
    {
        memcpy(_data, source, size);
        _size = size;
    }

    uint16_t size()
    {
        return _size;
    }

    uint8_t* data()
    {
        return _data;
    }
};