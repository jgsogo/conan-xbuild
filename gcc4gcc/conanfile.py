
import os
from conans import ConanFile, CMake
from conans.errors import ConanInvalidConfiguration

class gcc(ConanFile):
    name = "gcc4gcc"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "target": "ANY"}
    default_options = {"shared": False, "target": None}
    exports = "*"

    generators = "cmake", "cmake_find_package"

    def configure(self):
        settings_target = getattr(self, 'settings_target', None)
        if settings_target is None:
            # It is running in 'host', so Conan is compiling GCC package
            self.output.info(">>>> Running in 'host' context (compiling it)")
            if not self.options.target:
                self.options.target = self.settings.build_type  # Assume native compilation
                self.output.info(f">>>>  - Assume it will be a native compiler: target='{self.options.target}'")
            else:
                self.output.info(f">>>>  - It is a generic cross compiler: target='{self.options.target}'")
        else:
            # It is running in 'build' and it is being used as a BR
            self.output.info(">>>> Running in 'build' context")
            # Option target is computed from settings
            if self.options.target:
                raise ConanInvalidConfiguration(f">>>>  - Value for the option 'target' will be computed from settings_target (you provide '{self.options.target}')")
            self.options.target = self.settings_target.build_type

    def requirements(self):
        self.requires("zlib/0.1@user/testing")

    def build(self):
        # Check build_requires (build) are available
        self.output.write(">>>> gcc | gcc_exe")
        self.run("gcc_exe gcc", run_environment=True)

        # Run actual compilation
        cmake = CMake(self)
        settings = "|".join(map(str, [self.settings.os, self.settings.arch, self.settings.compiler, self.settings.build_type]))
        #options = "|".join(map(str, ["shared={}".format(self.options.shared), "target={}".format(self.options.target)]))
        options = "|".join(map(str, ["target={}".format(self.options.target)]))
        cmake.definitions["MESSAGE:STRING"] = " --> ".join([settings, options])
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("gcc_exe.*", src="bin", dst="bin", keep_path=False)
        self.copy("gcc_exe", src="bin", dst="bin", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["gcc"]
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))