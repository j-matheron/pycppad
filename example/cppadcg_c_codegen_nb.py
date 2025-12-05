from pycppad import (
    ADCGVector,
    CGVector,
    ADCG,
    CG,
    Independent,
    Value,
    ADCGFun,
    CodeHandler,
    LanguageC,
    LangCDefaultVariableNameGenerator,
)

# /***************************************************************************
#                               the model
# *************************************************************************/

# independent variable vector
n = 2

x = ADCGVector([ADCG(CG(2.0)), ADCG(CG(2.0))])

Independent(x)

# dependent variable vector
m = 1
y = ADCGVector()

# the model
a = x[0] / ADCG(CG(1.0)) + x[1] * x[1]
y.append(a / ADCG(CG(2.0)))

print(
    " y[0] :",
    y[0],
    " Value y[0]",
    Value(y[0]),
    "Value(y[0]).__int__ :",
    Value(y[0]).__int__,
    " with y type: ",
    type(y),
)

fun = ADCGFun(x, y)
# the model tape
print("ADCGFun", type(fun))


# /***************************************************************************
# *                        Generate the C source code
# **************************************************************************/

# /**
# * start the special steps for source code generation for a Jacobian
# */
handler = CodeHandler(50)
print("CodeHandler")

indVars = CGVector()
for i in range(n):
    indVars.append(CG(0.0))
print("CGVector")

handler.makeVariables(indVars)
print("indVars", indVars, type(indVars))

jac = fun.Jacobian(indVars)


langC = LanguageC("double", 3)
nameGen = LangCDefaultVariableNameGenerator("y", "x", "v", "array", "sarray")
code = handler.generateCode(langC, jac, nameGen, "source")
output = code.splitlines()
assert output[0] == "   y[1] = 0.5 * x[1] + 0.5 * x[1];"
assert output[1] == "   // dependent variables without operations"
assert output[2] == "   y[0] = 0.5;"
print(code)
