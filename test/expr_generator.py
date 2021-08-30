import random, sys

def createTerm():
    # coef = random.uniform(-sys.maxsize-1, sys.maxsize)
    # coef = random.randint(-sys.maxsize-1, sys.maxsize)
    coef = random.randint(-100, 100)
    power = random.randint(0, 2)
    term = "%s * X^%s"
    return term % (coef, power)

def createExpression(termsNum):
    expr = createTerm()
    for i in range(termsNum-1):
        t = createTerm()
        expr += (" " if t[0] == '-' else " + ") + t
    return expr

def main():
    org_stdout = sys.stdout
    with open("test/expressions.in", "w") as f:
        sys.stdout = f
        expressionsNum = 10
        expressions = []
        for i in range(expressionsNum):
            leftTermsNum = random.randint(1, 3)
            rightTermsNum = random.randint(1, 3)

            leftExpression = createExpression(leftTermsNum)
            rightExpression = createExpression(rightTermsNum)

            expression = leftExpression + " = " + rightExpression
            expressions.append(expression)

        for i in range(len(expressions)):
            print(expressions[i])
    sys.stdout = org_stdout

if __name__ == "__main__":
    main()
