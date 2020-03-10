
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

