
Export all the recipes, then:


Build the application for the 'host_profile' using some tools that are available to run in the 'build_profile':

```
conan install app/0.1@user/testing --build --profile:host=profiles/profile_host --profile:build=profiles/profile_build
```


* If we want the path to the application, we need to use the old behavior without profile_build:

  ```
  conan install app/0.1@user/testing -g virtualrunenv -g virtualenv --profile:host=profiles/profile_host
  ```

* Or use both profiles:

  ```
  conan install app/0.1@user/testing -g virtualrunenv -g virtualenv --profile:host=profiles/profile_host --profile:build=profiles/profile_build
  ```


Cross building
==============

This repository provides a fake GCC to emulate a cross-compiler. It is just an executable that 
modifies the source of the libraries to add a message about itself. After it, you'll need to run
the actual compiler.


Compiling the cross compiler
----------------------------

Without providing the value for option `target` it will assume it is a
native copiler and will take the value of the option from the `settings` (host).

* Compile old approach (only provide `profile_host`):

  ```bash
  $ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host
  ```

  It will assume it is a native compiler (Debug -> Debug or Release -> Release):

  ```bash
  $ conan install gcc/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host

    ...
    gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
    gcc/0.1@user/testing: >>>>  - Assume it will be a native compiler: target='Release'
    ...
    gcc/0.1@user/testing: Package 'de12e66171b9e7b69fc8a4b49f438efd9221bad8' created
  ```

  ```
  $ source ./_install/activate_run.sh && gcc_exe && source ./_install/deactivate_run.sh

    > gcc_exe
    > gcc_header: Macos|x86_64|apple-clang|Release --> target=Release
    > gcc: Macos|x86_64|apple-clang|Release --> target=Release
        > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
        > zlib: Macos|x86_64|apple-clang|Release|shared=True
    You need to provide a project to modify
  ```

  Here we see that the `gcc` is compiled in `Release` and it is targeting `Release`.

* Compile with the two profiles: result will be the same as there are no `build_requires`.

We can **provide the value of the `target` option** to compile `gcc` as a
cross compiler (`target` equals to `settings.build_type` should be a
already available as it is the one we generated before)

* Compile for target `Debug`:

  ```bash
  $ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host -o gcc:target=Debug

  ...
  gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
  gcc/0.1@user/testing: >>>>  - It is a generic cross compiler: target='Debug'
  ...
  gcc/0.1@user/testing: Package '8f8dc454df92757c35a13ee9b373bb7382b654aa' created
  ```

  ```bash
  $ conan install gcc/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host -o gcc:target=Debug
  $ source ./_install/activate_run.sh && gcc_exe && source ./_install/deactivate_run.sh

  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Release --> target=Debug
  > gcc: Macos|x86_64|apple-clang|Release --> target=Debug
      > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
      > zlib: Macos|x86_64|apple-clang|Release|shared=True
  You need to provide a project to modify
  ```

* Compile for target `Release`:

  ```bash
  $ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host -o gcc:target=Release
  ...
  gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
  gcc/0.1@user/testing: >>>>  - It is a generic cross compiler: target='Release'
  ...
  gcc/0.1@user/testing: Package 'de12e66171b9e7b69fc8a4b49f438efd9221bad8' created
  ```

  It is the generic cross compiler, but the package is the same generated in the
  first section.


Using the cross compiler as `build_requires`
--------------------------------------------

Now we are going to use the `gcc` package as a `build_requires`, I'll add it
to the `profiles/profile_gcc`. Because this is not an actual compiler, I need
to modify the recipes we are going to compile


**Using only the `profile:host`**

If we use only the `profile:host` we need the `target` option to select the
proper `gcc` package to use:

* By default it will take the value for the `target` from the `settings`:

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc
  ...
  gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
  gcc/0.1@user/testing: >>>>  - Assume it will be a native compiler: target='Release'
  ...
  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Release --> target=Release
  > gcc: Macos|x86_64|apple-clang|Release --> target=Release
      > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
      > zlib: Macos|x86_64|apple-clang|Release|shared=True
  ...
  testtool/0.1@user/testing: Package 'd4b0d76d52306bb4cf2651e562f26ab2600f8fe6' created
  ```

  ```bash
  $ conan install testtool/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host --profile:host=profiles/profile_gcc
  ...
      testtool/0.1@user/testing:d4b0d76d52306bb4cf2651e562f26ab2600f8fe6 - Cache
  ...
  ```

  And, the same without `build_requires` as they are not included in the package ID:

  ```bash
  $ conan install testtool/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host
  ...
      testtool/0.1@user/testing:d4b0d76d52306bb4cf2651e562f26ab2600f8fe6 - Cache
  ...
  ```

  We can run this binary and see it is using the native compiler (Release -> Release)

  ```bash
  $ source ./_install/activate_run.sh && testtool_exe && source ./_install/deactivate_run.sh
  > testtool_exe: Macos|x86_64|apple-clang|Release|shared=True
  > testtool_header: Macos|x86_64|apple-clang|Release|shared=True
  > -- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release
  > testtool: Macos|x86_64|apple-clang|Release|shared=True
    > testlib_header: Macos|x86_64|apple-clang|Release|shared=True
    > -- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release
    > testlib: Macos|x86_64|apple-clang|Release|shared=True
        > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
        > zlib: Macos|x86_64|apple-clang|Release|shared=True
  ```

* We can force to use a cross compiler using the `target` option:

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc -o gcc:target=Debug
  ```

  **Note.- Then we need to use the proper `settings` to match the compiler 
  output!!!** or the settings information will be misleading

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc -o gcc:target=Debug -s build_type=Debug
  ```

  What happens? We have added `-s build_type=Debug` and it applies to all the
  packages in the graph, also for `gcc` itself and the binary is not available.

  With this model **we cannot use the _release cross compiler_** and here I'm
  not going to talk about `os_build` and `arch_build` and ghosting the 
  `build_type`, we are here to make it the right way.

  Dead end.

**Using `profile_host` and `profile_build`**

Working with the new model, we can use two full profiles and avoid using the
`target` option. Next examples should be self explanatory (note that the `gcc`
as build require is applied to the `profile:host`):

* Cross compilation:

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:build=profiles/profile_build --profile:host=profiles/profile_gcc
  ...
  Configuration (profile_host):
  [settings]
  build_type=Release
  ...
  Configuration (profile_build):
  [settings]
  build_type=Debug
  ...
  gcc/0.1@user/testing: >>>> Running in 'build' context
  ...
  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Debug --> target=Release
  > gcc: Macos|x86_64|apple-clang|Debug --> target=Release
    > zlib_header: Macos|x86_64|apple-clang|Debug|shared=True
    > zlib: Macos|x86_64|apple-clang|Debug|shared=True
  ...
  testtool/0.1@user/testing: Package 'd4b0d76d52306bb4cf2651e562f26ab2600f8fe6' created
  ```

  We can see that `gcc` is using the `Debug` binary and it is using 
  `target=Release` because it is _cross compiling_ to the `profile_host`
  which is declared as `build_type=Release`.

  Indeed, the generated binary proves this behavior:

  ```bash
  $ conan install testtool/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host
  $ source ./_install/activate_run.sh && testtool_exe && source ./_install/deactivate_run.sh
  > testtool_exe: Macos|x86_64|apple-clang|Release|shared=True
  > testtool_header: Macos|x86_64|apple-clang|Release|shared=True
  > -- Compiled with GCC: Macos|x86_64|apple-clang|Debug --> target=Release
  > testtool: Macos|x86_64|apple-clang|Release|shared=True
    > testlib_header: Macos|x86_64|apple-clang|Release|shared=True
    > -- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release
    > testlib: Macos|x86_64|apple-clang|Release|shared=True
        > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
        > zlib: Macos|x86_64|apple-clang|Release|shared=True
  ```

  It is a `Release` application compiled with `gcc` in `Debug` mode targeting
  `Release`.

* We can run a _native compilation_ if we use `gcc` with `build_type=Release`.
  Easy, just use `--settings:build build_type=Release`:

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:build=profiles/profile_build --profile:host=profiles/profile_gcc -s:b build_type=Release
  ...
  testtool/0.1@user/testing: Package 'd4b0d76d52306bb4cf2651e562f26ab2600f8fe6' created
  ...
  $ conan install testtool/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host
  $ source ./_install/activate_run.sh && testtool_exe && source ./_install/deactivate_run.sh
  > testtool_exe: Macos|x86_64|apple-clang|Release|shared=True
  > testtool_header: Macos|x86_64|apple-clang|Release|shared=True
  > -- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release
  > testtool: Macos|x86_64|apple-clang|Release|shared=True
    > testlib_header: Macos|x86_64|apple-clang|Release|shared=True
    > -- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release
    > testlib: Macos|x86_64|apple-clang|Release|shared=True
        > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
        > zlib: Macos|x86_64|apple-clang|Release|shared=True
  ```

  It has used the `Release` binary from `gcc` to target a `Release` compilation.


**Note**

> Did you see a problem here? We are getting the same package ID for the `testtool`
application and it is a different binary (the cross compiler modifies the
sources). This is not a problem of this model, this is because `build_requires`
are not encoded into the package ID. Not to be discussed here.


Cross compiling a cross compiler
--------------------------------

Can we make it all? Let's try it! I'll be using the package `gcc4gcc`
because our _cross compiling_ works modifying the sources and we need
to call it explicitly. Actuall cross compiler will populate `CC` and
`CXX` variables (probably more) and it will work out of the box.

```bash
$ conan create gcc4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:build=profiles/profile_build --profile:host=profiles/profile_gcc
...
```
