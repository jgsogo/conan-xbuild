
import os
from conans import ConanFile, CMake

class app(ConanFile):
    name = "app"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    exports = "*"

    
    generators = "cmake", "cmake_find_package"

    def requirements(self):
        self.requires("library/0.1@user/testing")

    def build_requirements(self):
        self.build_requires("cmake/0.1@user/testing")
        self.build_requires("testtool/0.1@user/testing", force_host_context=True)

    def build(self):
        # Check build_requires (build) are available
        self.output.write(">>>> cmake | cmake_exe")
        self.run("cmake_exe.exe", run_environment=True)

        # Run actual compilation
        cmake = CMake(self)
        settings = "|".join(map(str, [self.settings.os, self.settings.arch, self.settings.compiler, self.settings.build_type]))
        options = "|".join(map(str, ["shared={}".format(self.options.shared)]))
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
        self.copy("app_exe.*", src="bin", dst="bin", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["app"]
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))