from conans import ConanFile

class Recipe(ConanFile):
    name = "gcc4gcc"
    python_requires = "gcc/0.1@user/testing"
    python_requires_extend = "gcc.gcc"

    def build(self):
        # Check build_requires (build) are available
        self.output.write(">>>> gcc | gcc_exe")
        self.run("gcc_exe testtool", run_environment=True)

        super(Recipe, self).build()
