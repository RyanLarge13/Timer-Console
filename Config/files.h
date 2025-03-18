#ifndef FILES_H
#define FILES_H


class Files {
  public:
  Files();

  #ifdef _WIN32
  const string HOME_DIR = getenv("USERPROFILE");
  #elif defined(__APPLE__)
  const string HOME_DIR = getenv("HOME");
  #elif defined(__linux__)
  const string HOME_DIR = getenv("HOME");
  #elif defined(__ANDROID__)
  const string HOME_DIR = "/data/data/com.termux/files/home";
  #else
  const string HOME_DIR = getenv("HOME");
  #endif

  void getTimers();
  void getAlarms();
  void getStopwatch();

  void setTimers();
  void setAlarms();
  void setStopwatch();

  protected:
  private:
};

#endif