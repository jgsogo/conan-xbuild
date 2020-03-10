
import os
from conans import ConanFile, CMake

class cmake(ConanFile):
    name = "cmake"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    exports = "*"

    generators = "cmake", "cmake_find_package"
    

    def requirements(self):
        self.requires("cmakelib/0.1@user/testing")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["MESSAGE:STRING"] = "|".join(map(str, [self.settings.os, self.settings.arch, self.settings.compiler, self.settings.build_type]))
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", keep_path=True)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("cmake_exe", src="bin", dst="bin", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["cmake"]
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))