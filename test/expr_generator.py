import random, sys

def createTerm(bigNumbers):
    minmax = (-sys.maxsize-1, sys.maxsize) if bigNumbers else (-100, 100)
    coef = random.randint(minmax[0], minmax[1])
    power = random.randint(0, 2)
    term = "%s * X^%s"
    return (term % (coef*(-1) if coef < 0 else coef, power), coef < 0)

def createExpression(termsNum, bigNumbers):
    expr = ""
    for i in range(termsNum):
        t = createTerm(bigNumbers)
        if not expr:
            expr += t[0]
        else:
            expr += (" - " if t[1] else " + ") + t[0]
    return expr

def main():
    org_stdout = sys.stdout
    with open("test/expressions.in", "w") as f:
        sys.stdout = f
        expressionsNum = 10
        expressions = []
        bigNumbers = 0
        for i in range(expressionsNum):
            leftTermsNum = random.randint(1, 3)
            rightTermsNum = random.randint(1, 3)

            leftExpression = createExpression(leftTermsNum, bigNumbers)
            rightExpression = createExpression(rightTermsNum, bigNumbers)

            expression = leftExpression + " = " + rightExpression
            expressions.append(expression)

        for i in range(len(expressions)):
            print(expressions[i])
    sys.stdout = org_stdout

if __name__ == "__main__":
    main()
