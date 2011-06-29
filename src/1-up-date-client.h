#ifndef ONE_UP_DATE_CLIENT_H_
#define ONE_UP_DATE_CLIENT_H_

#include <cstddef>
#include <string>

bool StartOneUpDateClient(const std::size_t timeout,
                          const std::string &current_version_id);

void TerminateOneUpDateClient(void);

#endif // ONE_UP_DATE_CLIENT_H_
