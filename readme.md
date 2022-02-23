# GetIt

[![Build & Test GetIt](https://github.com/bartkessels/GetIt/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/bartkessels/GetIt/actions/workflows/build_and_test.yml)

---

Welcome to the Git repository of GetIt. GetIt is a small open source application to send API
request using a cross-platform GUI. The main advantage of GetIt is the fact that it's native, no
matter what platform you use, and it's completely open source.

As of right now GetIt is undergoing a massive rewrite to make the application more stable and
testable. This means that the branch you're currently watching (main) most likely contains a
broken build. If you need a working copy of GetIt please checkout the `main_old` or `master`
branches.

The current state of GetIt is that the core functionality is done, thus meaning that it's able
to send a request and receive the response. This is however only possible by using the classes
directly (in other words, you need to modify the code yourself). The UI is another hurdle that
I'm trying to tackle in the best possible way, meaning that I want to decouple the UI logic from
the UI to make it testable. As of right now I've no exact idea of how I want (or going) to
accomplish this. So please check back in a couple of weeks to view the progress!

__UPDATE__

As of today (february 21st) the UI of GetIt is done and functional! The only thing left
is saving and opening a request and error-handling (i.e. in a way that you, the user, sees
wat went wrong instead of a segfault).

![Main screen of GetIt](resources/images/getit.png)

For more information about the motives behind the (re)design of GetIt, please checkout the [documentation](docs/design.md).
