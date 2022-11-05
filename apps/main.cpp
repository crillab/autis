#include "../libs/universe/libs/easy-jni/easyjni/JavaVirtualMachineBuilder.h"
#include "../libs/universe/libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"
#include "../libs/universe/universe/include/utils/JavaSolverFactory.hpp"
#include "../autis/xcsp/AutisUniverseCspSolverDecorator.hpp"

int main(){
    easyjni::JavaVirtualMachineBuilder builder = easyjni::JavaVirtualMachineBuilder();
    builder.addToClasspath("./jar/juniverse.jar");
    builder.addToClasspath("./jar/ACE.jar");
    builder.addToClasspath("./jar/assurancetourix.jar");
    builder.addToClasspath("./jar/xcsp3-tools-2.0.1.jar");
    builder.setVersion(JNI_VERSION_10);
    auto jvm = builder.buildJavaVirtualMachine();
    easyjni::JavaVirtualMachineRegistry::set(jvm);

    auto factory = new Universe::JavaSolverFactory("fr/univartois/cril/assurancetourix/AceSolverFactory");
    auto solver = factory->createCspSolver();

    FILE* f = fopen("./apps/example.xml","r");
    auto* d = new Autis::AutisUniverseCspSolverDecorator(solver, f);
    d->parse();
    d->solve();
    return 0;
}