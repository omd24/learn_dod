#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

//---------------------------------------------------------------------------//
// Resources (data oriented access macros)
//---------------------------------------------------------------------------//

#define SOA(_element, _ref) ms_Data._element.getByRef(_ref, ms_Generations)
#define SOA_GET_VALUE(_element, _ref)                                          \
  ms_Data._element.getValueByRef(_ref, ms_Generations)
#define SOA_SET_VALUE(_element, _ref, _value)                                  \
  ms_Data._element.setValueByRef(_ref, _value, ms_Generations)

#define DEBUG_BREAK(expr)                                                      \
  if (!(expr))                                                                 \
  {                                                                            \
    __debugbreak();                                                            \
  }
#define ERROR_DIALOG(_msg)                                                     \
  {                                                                            \
    const int result =                                                         \
        MessageBoxA(NULL, _msg, "Error", MB_ICONERROR | MB_ABORTRETRYIGNORE);  \
    switch (result)                                                            \
    {                                                                          \
    case IDABORT:                                                              \
      _exit(0);                                                                \
      break;                                                                   \
    case IDRETRY:                                                              \
      DEBUG_BREAK();                                                           \
      break;                                                                   \
    case IDCONTINUE:                                                           \
      break;                                                                   \
    }                                                                          \
  }
#define ERROR_DIALOG_SIMPLE(_msg)                                              \
  MessageBoxA(NULL, _msg, "[RENDERER] Error", MB_ICONERROR | MB_OK)

// Direct3D 12:

#include <wrl/client.h>
#include <d3d12.h>
#include "d3dx12.h"
#include <DXGI1_4.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#define DX12_CHECK_RESULT(x) assert(SUCCEEDED(x) && "Result != SUCCEEDED")

#define DX12_EXEC_CHECKED(x)                                                   \
  {                                                                            \
    HRESULT xx = x;                                                            \
    DX12_CHECK_RESULT(xx);                                                     \
  }

// ============================================

#include <string>
#include <vector>

#define RNR_DATA_FIELDS                                                        \
  RNR_FIELD(std::string, name);                                                \
  RNR_FIELD(bool, flag);                                                       \
                                                                               \
  RNR_FIELD(std::string, lastname);                                            \
  RNR_FIELD(std::vector<int>, scores);

//---------------------------------------------------------------------------//
struct BaseDataSlice
{
#define RNR_FIELD(_type, _name) _type _name
  RNR_DATA_FIELDS
#undef RNR_FIELD
};
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
/// SOA base data
//---------------------------------------------------------------------------//
struct BaseData
{
  void resize(uint32_t p_Capacity)
  {

#define RNR_FIELD(_type, _name) _name.resize(p_Capacity)
    RNR_DATA_FIELDS
#undef RNR_FIELD
  }

#define RNR_FIELD(_type, _name) std::vector<_type> _name
  RNR_DATA_FIELDS
#undef RNR_FIELD
};
//---------------------------------------------------------------------------//

int main()
{

  return (0);
}
