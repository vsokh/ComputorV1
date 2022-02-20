import random
import sys


class MonomialCreator:
    def __init__(self, coef_limit=100, degree_limit=2):
        self._coef_limit = coef_limit
        self._degree_limit = degree_limit

    def create(self):
        coefficient = self.__create_coefficient()
        degree = self.__create_degree()
        return "%s * X^%s" % (coefficient, degree)

    def __create_coefficient(self):
        if random.randint(0, 1):
            coefficient = round(random.uniform(0, self._coef_limit), 2)
        else:
            coefficient = random.randint(0, self._coef_limit)
        return coefficient

    def __create_degree(self):
        degree = random.randint(0, self._degree_limit)
        return degree


class PolynomialCreator:
    def __init__(self, left_monomials_limit=3, right_monomials_limit=3, coefficient_limit=100, degree_limit=2):
        self._left_monomials_limit = left_monomials_limit
        self._right_monomials_limit = right_monomials_limit

        self._monomial_creator = MonomialCreator(coefficient_limit, degree_limit)

    def create(self):
        left_polynomial = self.__create(self._left_monomials_limit)
        right_polynomial = self.__create(self._right_monomials_limit)
        return "%s = %s" % (left_polynomial, right_polynomial)

    def __create(self, monomials_limit):
        polynomial = ""
        for _ in range(monomials_limit):
            monomial = self._monomial_creator.create()

            if polynomial:
                if random.randint(0, 1):
                    polynomial += " - "
                else:
                    polynomial += " + "

            polynomial += monomial
        return polynomial


def main():
    org_stdout = sys.stdout
    # TODO: check args' amount
    with open(sys.argv[1], "w") as file:
        sys.stdout = file

        polynomials = [PolynomialCreator().create() for _ in range(10)]
        [print(p) for p in polynomials]

    sys.stdout = org_stdout


if __name__ == "__main__":
    main()