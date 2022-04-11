
struct DataBase
{
private:
  int m_Capacity;
};

struct StudentData : DataBase
{
  int m_Score;
};

struct StudentManager
{
  static StudentData ms_Data;
};

StudentData StudentManager::ms_Data;

int main()
{

  return (0);
}
