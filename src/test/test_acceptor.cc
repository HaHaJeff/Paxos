#include "acceptor.h"

int main()
{
  std::shared_ptr<StateMachine> pState = std::make_shared<StateMachine>();
  Acceptor a(pState);
  return 0;
}
