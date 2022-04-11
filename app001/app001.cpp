#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

struct DataBase
{
public:
  DataBase() : m_Capacity(0u), m_RecordSize(0u)
  {
  }
  virtual void init(uint32_t p_Capacity) = 0;
  uint32_t m_Capacity;
  uint32_t m_RecordSize;
};

struct StudentData : DataBase
{
  float* m_Score;
  uint32_t* m_Age;

  void init(uint32_t p_Capacity) override
  {
    m_Capacity = p_Capacity;
    m_RecordSize = sizeof(float) * sizeof(uint32_t);

    uint32_t memSize = m_RecordSize * m_Capacity;
    uint8_t* dataMem = (uint8_t*)::malloc(memSize);
    uint8_t* dataMemCursor = dataMem;

    ::memset(dataMem, 0, memSize);

    m_Score = (float*)dataMemCursor;
    dataMemCursor += m_Capacity * sizeof(float);
    m_Age = (uint32_t*)dataMemCursor;
    dataMemCursor += m_Capacity * sizeof(uint32_t);
  }
};

template <typename T> struct ObjectManagerBase
{
  static T ms_Data;
};
template <typename T> T ObjectManagerBase<T>::ms_Data;

struct StudentManager : ObjectManagerBase<StudentData>
{
  static void init(uint32_t p_Capacity)
  {
    ms_Data.init(p_Capacity);
  }
};

// add live obj count
//
//
//

int main()
{

  StudentManager studentMgr = {};
  studentMgr.init(10);

  for (size_t i = 0; i < 10; i++)
  {
    studentMgr.ms_Data.m_Age[i] = 15;
    studentMgr.ms_Data.m_Score[i] = 20.0f;
  }

  return (0);
}
