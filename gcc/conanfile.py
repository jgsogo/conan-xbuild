
import os
from conans import ConanFile, CMake

class gcc(ConanFile):
    name = "gcc"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "target": [None, "DEBUG", "RELEASE"]}
    default_options = {"shared": False, "target": None}
    exports = "*"

    generators = "cmake", "cmake_find_package"

    def configure(self):
        if not self.options.target:
            self.output.info("By default, native compilation (equals host_profile: '{}')".format(str(self.settings.build_type).upper()))
            self.options.target = str(self.settings.build_type).upper()

    def requirements(self):
        self.requires("zlib/0.1@user/testing")

    def build(self):
        # Run actual compilation
        cmake = CMake(self)
        settings = "|".join(map(str, [self.settings.os, self.settings.arch, self.settings.compiler, self.settings.build_type]))
        options = "|".join(map(str, ["shared={}".format(self.options.shared), "target={}".format(self.options.target)]))
        cmake.definitions["MESSAGE:STRING"] = "|".join([settings, options])
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