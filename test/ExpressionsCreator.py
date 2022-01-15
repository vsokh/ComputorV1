import random
import sys

class TermCreator:
    def __init__(self, coefLimit=100, powerLimit=2):
        self._coefLimit = coefLimit
        self._powerLimit = powerLimit

    def create(self):
        coef = self.__createCoef()
        power = self.__createPower()
        return "%s * X^%s" % (coef, power)

    def __createCoef(self):
        if random.randint(0, 1):
            coef = round(random.uniform(0, self._coefLimit), 2)
        else:
            coef = random.randint(0, self._coefLimit)
        return coef

    def __createPower(self):
        power = random.randint(0, self._powerLimit)
        return power

class ExpressionCreator:
    def __init__(self, leftTermsLimit=3, rightTermsLimit=3, coefLimit=100, powerLimit=2):
        self._leftTermsLimit = leftTermsLimit
        self._rightTermsLimit = rightTermsLimit

        self._termCreator = TermCreator(coefLimit, powerLimit)

    def create(self):
        leftExpr = self.__create(self._leftTermsLimit)
        rightExpr = self.__create(self._rightTermsLimit)
        return "%s = %s" % (leftExpr, rightExpr)

    def __create(self, termsLimit):
        expr = ""
        for _ in range(termsLimit):
            term = self._termCreator.create()

            if expr:
                if random.randint(0, 1):
                    expr += " - "
                else:
                    expr += " + "

            expr += term
        return expr

def main():
    org_stdout = sys.stdout
    # TODO: check args' amount
    with open(sys.argv[1], "w") as file:
        sys.stdout = file

        expressions = [ExpressionCreator().create() for _ in range(10)]
        [print(expr) for expr in expressions]

    sys.stdout = org_stdout

if __name__ == "__main__":
    main()
