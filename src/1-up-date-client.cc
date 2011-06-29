#include "1-up-date-client.h"
#include <string>
#include <windows.h>
#include <cstddef>
#include <cstdlib>
#include <cstdio>

struct OneUpDateParams {
  std::size_t timeout;
  std::string current_version_id;
};

bool CheckForNewVersion(std::string *new_version_id) {
  *new_version_id = "1.0.0b";
  return true;
}

HANDLE event_quit_thread;
bool quit_thread;

DWORD WINAPI OneUpDateClient(LPVOID param) {
  OneUpDateParams *params = static_cast<OneUpDateParams *>(param);

  std::string new_version_id;
  while (!CheckForNewVersion(&new_version_id) && !quit_thread)
    WaitForSingleObject(event_quit_thread, params->timeout);

  if (quit_thread) {
    std::printf("Program finished, going out\n");
    return 0;
  }

  std::printf("Updating\n");

  // Download new version
  // download version hash
  // Check version hash
  // unpack new version
  // launch helper program
  return 0;
}

HANDLE thread_handle;
DWORD thread_id;

bool StartOneUpDateClient(const std::size_t timeout,
                          const std::string &current_version_id) {
  event_quit_thread = CreateEvent(NULL, TRUE, FALSE, "QuitUpdater");
  quit_thread = false;

  OneUpDateParams *params = new OneUpDateParams;
  params->timeout = timeout;
  params->current_version_id = current_version_id;

  std::printf("about to create thread\n");

  thread_handle = CreateThread(NULL, 0, OneUpDateClient, params, 0, &thread_id);

  std::printf("thread created\n");
}

void TerminateOneUpDateClient(void) {
  quit_thread = true;
  SetEvent(event_quit_thread);
  WaitForSingleObject(thread_handle, INFINITE);
}
  
