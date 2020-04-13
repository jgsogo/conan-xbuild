
Notes about virtualenvs
=======================

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
  ...
  [settings]
  build_type=Release
  ..
  gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
  gcc/0.1@user/testing: >>>>  - Assume it will be a native compiler: target='Release'
  ...
  gcc/0.1@user/testing: Package 'de12e66171b9e7b69fc8a4b49f438efd9221bad8' created
  ```

  > **Note**.- You can see an error, the recipe is trying to use a `gcc_exe`
  that is not available yet. Don't worry about it, the is a try/catch for it.

  It will assume it is a native compiler (`Debug` -> `Debug` or 
  `Release` -> `Release`):

  ```bash
  $ conan install gcc/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host
    ...
    Packages
      gcc/0.1@user/testing:de12e66171b9e7b69fc8a4b49f438efd9221bad8 - Cache
  ```

  ```bash
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

  ```bash
  $ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:build=profiles/profile_build
  ```

We can **provide the value of the `target` option** to compile `gcc` as a
cross compiler (by default, the option `target` takes its value from
`settings.build_type`, it is the one we generated before)

* Compile for target `Debug`:

  ```bash
  $ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host -o gcc:target=Debug
  ...
  Configuration:
  [settings]
  build_type=Release
  [options]
  gcc:target=Debug
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
to the `profiles/profile_gcc`.


**Using only the `profile:host`**

If we use only the `profile:host` we need the `target` option to select the
proper `gcc` package to use:

* By default it will take the value for the `target` from the `settings`:

  ```bash
  $ conan create testtool/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc
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

  And we can run the same without `build_requires` as they are not included in the package ID:

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

  As we can see in the output, `testtool` and its libraries have been compiled
  using the native compiler: `-- Compiled with GCC: Macos|x86_64|apple-clang|Release --> target=Release`


* We can force to use a cross compiler using the `target` option:

  ```bash
  $ conan create testtool/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc -o gcc:target=Debug
  ...
  Configuration:
  [settings]
  build_type=Release
  ...
  testtool/0.1@user/testing: >>>> gcc | gcc_exe
  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Release --> target=Debug
  > gcc: Macos|x86_64|apple-clang|Release --> target=Debug
    > zlib_header: Macos|x86_64|apple-clang|Release|shared=True
    > zlib: Macos|x86_64|apple-clang|Release|shared=True
  ```

  > **Note.- With this old approach (only one profile), we need to use the
  proper `settings` to match the compiler output!!!** or the settings
  information will be misleading

  ```bash
  $ conan create testtool4gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:host=profiles/profile_gcc -o gcc:target=Debug -s build_type=Debug
  ...
  Configuration:
  [settings]
  build_type=Debug
  [options]
  gcc:target=Debug
  ...
  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Debug --> target=Debug
  > gcc: Macos|x86_64|apple-clang|Debug --> target=Debug
    > zlib_header: Macos|x86_64|apple-clang|Debug|shared=True
    > zlib: Macos|x86_64|apple-clang|Debug|shared=True
  ...
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
  [build_requires]
  *: gcc/0.1@user/testing
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
  ```

  ```bash
  $ conan install testtool/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host
  ```

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

  It has used the `Release` binary from `gcc` to target a `Release` compilation.


> **Note.-** Did you see a problem here? We are getting the same package ID for the `testtool`
application and it is a different binary (the cross compiler modifies the
sources). This is not a problem of this model, this is because `build_requires`
are not encoded into the package ID. Not to be discussed here.


Cross compiling a cross compiler
--------------------------------

> **Note.-** Start from scratch, remove all the packages from your cache.

Can we make it all? Let's try it! 

First we need the compiler that will run in our `build` machine targeting
the `host` machine. As this will be a cross compiler be need to pass
the option `target` explicitly:

```bash
$ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_build --profile:build=profiles/profile_build --options:host gcc:target=Release
...
Configuration (profile_host):
[settings]
build_type=Debug
[options]
gcc:target=Release
...
Configuration (profile_build):
[settings]
build_type=Debug
...
gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
gcc/0.1@user/testing: >>>>  - It is a generic cross compiler: target='Release'
...
# There is no `gcc_exe` as build requires, our try/catch takes care of it.
gcc/0.1@user/testing: >>>> gcc | gcc_exe
/bin/sh: gcc_exe: command not found
gcc/0.1@user/testing: --- gcc not ready
...

```

Let's run our brand new *cross compiler* (from `Debug` to `Release`):

```bash
$ conan install gcc/0.1@user/testing -g virtualrunenv -if _install --profile:host=profiles/profile_build --options:host gcc:target=Release
```

```bash
$ source ./_install/activate_run.sh && gcc_exe && source ./_install/deactivate_run.sh
> gcc_exe
> gcc_header: Macos|x86_64|apple-clang|Debug --> target=Release
> gcc: Macos|x86_64|apple-clang|Debug --> target=Release
	> zlib_header: Macos|x86_64|apple-clang|Debug|shared=True
	> zlib: Macos|x86_64|apple-clang|Debug|shared=True
You need to provide a project to modify
```

Now, **let's use this cross compiler to cross compile another cross compiler**
(general scenario, Canadian cross). I will split the output of the command into
parts so we can see each one of them isolated:

```bash
$ conan create gcc/conanfile.py user/testing --profile:host=profiles/profile_host --profile:build=profiles/profile_build --profile:host=profiles/profile_gcc --options:host gcc:target=Debug
```

* Settings and options: everything is ok, there is no need to tell the `gcc`
  that is acting as build requires, which is the target configuration to use.

  ```bash
  ...
  Configuration (profile_host):
  [settings]
  build_type=Release
  [options]
  gcc:target=Debug
  [build_requires]
  *: gcc/0.1@user/testing
  [env]

  Configuration (profile_build):
  [settings]
  build_type=Debug
  ```

* Conan selects the proper package IDs:
  
  ```bash
  gcc/0.1@user/testing: >>>> Running in 'host' context (compiling it)
  gcc/0.1@user/testing: >>>>  - It is a generic cross compiler: target='Debug'
  gcc/0.1@user/testing: Forced build from source
  gcc/0.1@user/testing: >>>> Running in 'build' context
  gcc/0.1@user/testing: Forced build from source
  Installing package: gcc/0.1@user/testing
  Requirements
      gcc/0.1@user/testing from local cache - Cache
      zlib/0.1@user/testing from local cache - Cache
  Packages
      gcc/0.1@user/testing:8f8dc454df92757c35a13ee9b373bb7382b654aa - Build
      zlib/0.1@user/testing:e992dca89c56300b2901b18c23dbae33f62b3a9e - Cache
  Build requirements
      gcc/0.1@user/testing from local cache - Cache
      zlib/0.1@user/testing from local cache - Cache
  Build requirements packages
      gcc/0.1@user/testing:9e91d80a26aa8e17015d4b9d327120ecbb89abe3 - Build
      zlib/0.1@user/testing:d182ba58b0d1d0d375072af5bab5ee0790f469dd - Cache
  ```

  The `gcc` acting as build requires is `gcc/0.1@user/testing:9e91d80a26aa8e17015d4b9d327120ecbb89abe3` which is the `Debug` build
  targeting `Release`.

  `gcc` to build is `gcc/0.1@user/testing:8f8dc454df92757c35a13ee9b373bb7382b654aa` which is `Release` binary
  targeting `Debug`

  > **Note.-** We already have a problem here. Conan identifies that it has
  to build both packages (Conan uses the name). I don't know how to
  disambiguate this, or much worse, the `--build gcc` in the command line.

* Conan build the `gcc` acting as build requires:

  ```bash
  ...
  gcc/0.1@user/testing: >>>> gcc | gcc_exe
  /bin/sh: gcc_exe: command not found
  gcc/0.1@user/testing: --- gcc not ready
  ...
  gcc/0.1@user/testing: Package '9e91d80a26aa8e17015d4b9d327120ecbb89abe3' created
  ```

  `gcc_exe` fails to run, it is ok, this recipe doesn't have `gcc` as
  build_requires.

* Conan build the `gcc` for the host machine:

  ```bash
  ...
  gcc/0.1@user/testing: >>>> gcc | gcc_exe
  > gcc_exe
  > gcc_header: Macos|x86_64|apple-clang|Debug --> target=Release
  > gcc: Macos|x86_64|apple-clang|Debug --> target=Release
    > zlib_header: Macos|x86_64|apple-clang|Debug|shared=True
    > zlib: Macos|x86_64|apple-clang|Debug|shared=True
  ...
  gcc/0.1@user/testing: Package '8f8dc454df92757c35a13ee9b373bb7382b654aa' created
  ```

  It uses the `gcc_exe` we have just built: `Debug` binary targeting `Release`.
  And Conan succesfully build the binary for the _host machine_.


Let's have a look to this final package:

```bash
$ conan install gcc/0.1@user/testing -g virtualrunenv -if _install --profile=profiles/profile_host -o:h gcc:target=Debug
...
Packages
    gcc/0.1@user/testing:8f8dc454df92757c35a13ee9b373bb7382b654aa - Cache
```

```bash
$ source ./_install/activate_run.sh && gcc_exe && source ./_install/deactivate_run.sh
> gcc_exe
> gcc_header: Macos|x86_64|apple-clang|Release --> target=Debug
> -- Compiled with GCC: Macos|x86_64|apple-clang|Debug --> target=Release
> gcc: Macos|x86_64|apple-clang|Release --> target=Debug
	> zlib_header: Macos|x86_64|apple-clang|Release|shared=True
	> zlib: Macos|x86_64|apple-clang|Release|shared=True
You need to provide a project to modify
```

Here we are running `gcc_exe` that has been compiled in `Release` and it is
targetting `Debug` (it is a cross compiler), and it has been _"Compiled with GCC"_ using a `Debug` binary that targets `Release` (also a cross compiler).

Piece of cake!

