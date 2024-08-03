# bazel-cpp-boilerplate

uniq - Unix Command line tool built for John Crickett's Coding Challenge.

## How to build and run

First, make sure you have [Bazel](https://bazel.build/install) installed.

```bash
bazel build :all
```

```bash
bazel-bin/uniq testdata/test.txt
```

## Running the tests

```bash
bazel test --test_output=all :all
```

## Autocomplete with Neovim

Because we are using Bazel, `clangd` autocomplete in Neovim doesn't know where to find the headers. To fix it, I'm using [Hedron's Compile Commands Extractor for Bazel](https://github.com/hedronvision/bazel-compile-commands-extractor).

Execute the following command to fix autocomplete when new dependencies are installed:

```
bazel run @hedron_compile_commands//:refresh_all
```

## Resources

- [Bazel](https://bazel.build/) as the build tool.
- [Google Test](https://google.github.io/googletest/) for testing.
- [Abseil](https://abseil.io/) as an opensource collection of C++ libraries.
- [Bazel Compile Commands Extractor](https://github.com/hedronvision/bazel-compile-commands-extractor) to support autocompletion in Neovim and IDEs.
