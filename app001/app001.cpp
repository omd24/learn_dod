#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include <deque>
typedef uint32_t LiveIndex;
typedef std::deque<uint32_t> Uint32Deque;

struct DataBase
{
  DataBase()
      : m_Capacity(0u),
        m_RecordSize(0u),
        m_DataMem(nullptr),
        m_LiveIndex(nullptr)
  {
  }
  virtual void init(uint32_t p_Capacity) = 0;
  virtual void shutdown() = 0;
  uint32_t m_Capacity;
  uint32_t m_RecordSize;
  uint8_t* m_DataMem;

  LiveIndex* m_LiveIndex;
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
    m_DataMem = (uint8_t*)::malloc(memSize);
    uint8_t* dataMemCursor = m_DataMem;

    ::memset(m_DataMem, 0, memSize);

    m_LiveIndex = (LiveIndex*)dataMemCursor;
    dataMemCursor += m_Capacity * sizeof(LiveIndex);
    m_Score = (float*)dataMemCursor;
    dataMemCursor += m_Capacity * sizeof(float);
    m_Age = (uint32_t*)dataMemCursor;
    dataMemCursor += m_Capacity * sizeof(uint32_t);
  }

  void shutdown() override
  {
    m_Age = nullptr;
    m_Score = nullptr;
    m_LiveIndex = 0;
    m_RecordSize = 0;
    m_Capacity = 0;

    ::free(m_DataMem);
    m_DataMem = nullptr;
  }
};

template <typename T> struct ObjectManagerBase
{
  static T ms_Data;
  static uint8_t* ms_LiveObjects;
  static uint32_t ms_LiveObjectCount;
  static uint32_t ms_LiveObjectCountMax;
  static Uint32Deque* ms_FreeIndices;
  static uint32_t ms_GenerationCount;

  /// The number of objects freed before reusing index slots
  static uint32_t OBJECT_MINIMUM_FREE_INDICES;
};

/// Static data definitions
template <typename T> T ObjectManagerBase<T>::ms_Data;

template <typename T> uint8_t* ObjectManagerBase<T>::ms_LiveObjects;

template <typename T> uint32_t ObjectManagerBase<T>::ms_LiveObjectCount;

template <typename T> uint32_t ObjectManagerBase<T>::ms_LiveObjectCountMax;

template <typename T>
std::deque<uint32_t>* ObjectManagerBase<T>::ms_FreeIndices = nullptr;

template <typename T> uint32_t ObjectManagerBase<T>::ms_GenerationCount;

template <typename T>
uint32_t ObjectManagerBase<T>::OBJECT_MINIMUM_FREE_INDICES = 1024;

struct StudentManager : ObjectManagerBase<StudentData>
{
  static void init(uint32_t p_Capacity)
  {
    _initializeDataBase(p_Capacity);

    // other specific initialization code
    //
  }
  static void shutdown()
  {
    _deallocateDataBase();
  }

  static void _initializeDataBase(uint32_t p_Capacity)
  {
    ms_Data.init(p_Capacity);
    ms_LiveObjectCount = 0;
    ms_LiveObjectCountMax = 0;
    ms_LiveObjects = (uint8_t*)::malloc(p_Capacity * sizeof(uint8_t));
    memset(ms_LiveObjects, 0xFFFFFFFF, p_Capacity * sizeof(uint8_t));

    ms_FreeIndices = new Uint32Deque();
  }
  static void _deallocateDataBase()
  {
    ms_Data.shutdown();

    delete ms_FreeIndices;

    ms_LiveObjects = nullptr;
    ms_FreeIndices = nullptr;
    ms_LiveObjectCount = 0u;
    ms_GenerationCount = 0u;
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

  studentMgr.shutdown();
  return (0);
}
