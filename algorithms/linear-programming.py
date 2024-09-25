class SimplexSolver:
    def __init__(self, func_coefficients):
        self.objective = []
        for func_coefficient in func_coefficients:
            self.objective.append(func_coefficient)
        self.rows = []
        self.constraints = []

    def solve(self):
        self.add_slack_variables()
        while self.should_pivot():
            col = self.get_pivot_col()
            row = self.get_pivot_row(col)
            self.pivot(row, col)

    def add_constraint(self, coefficients, value):
        row = []
        for coefficient in coefficients:
            row.append(coefficient)
        self.rows.append(row)
        self.constraints.append(value)

    def get_pivot_col(self):
        low = 0
        pivot_idx = 0
        for i in range(len(self.objective) - 1):
            if self.objective[i] < low:
                low = self.objective[i]
                pivot_idx = i
        return pivot_idx

    def get_pivot_row(self, col_idx):
        last_col = [self.rows[i][-1] for i in range(len(self.rows))]
        pivot_col = [self.rows[i][col_idx] for i in range(len(self.rows))]
        min_ratio = float("inf")
        min_ratio_idx = -1
        for i in range(len(last_col)):
            ratio = float("inf")
            if pivot_col[i] == 0:
                ratio = 99999999
            else:
                ratio = last_col[i] / pivot_col[i]
            if ratio < 0:
                continue
            if ratio < min_ratio:
                min_ratio = ratio
                min_ratio_idx = i
        if min_ratio_idx == -1:
            raise Exception("no non-negative ratios, problem doesn't have a solution")
        return min_ratio_idx

    def pivot(self, pivot_row_idx, pivot_col_idx):
        pivot_val = self.rows[pivot_row_idx][pivot_col_idx]
        for i in range(len(self.rows[pivot_row_idx])):
            self.rows[pivot_row_idx][i] = self.rows[pivot_row_idx][i] / pivot_val
        for i in range(len(self.rows)):
            if i == pivot_row_idx:
                continue
            mul = self.rows[i][pivot_col_idx]
            for j in range(len(self.rows[i])):
                self.rows[i][j] = self.rows[i][j] - mul * self.rows[pivot_row_idx][j]
        mul = self.objective[pivot_col_idx]
        for i in range(len(self.objective)):
            self.objective[i] = self.objective[i] - mul * self.rows[pivot_row_idx][i]

    def should_pivot(self):
        return min(self.objective[:-1]) < 0

    def add_slack_variables(self):
        for i in range(len(self.rows)):
            self.objective.append(0)
            basic_cols = [0] * len(self.rows)
            basic_cols[i] = 1
            basic_cols.append(self.constraints[i])
            self.rows[i] += basic_cols
        self.objective.append(0)

    def get_solution_from_tableau(self):
        cols = []
        for colI in range(len(self.rows[0])):
            col = [0] * len(self.rows)
            for rowI in range(len(self.rows)):
                col[rowI] = self.rows[rowI][colI]
            cols.append(col)

        results = []
        for i in range(len(cols) - 1):
            if cols[i].count(0) == len(cols[i]) - 1 and 1 in cols[i]:
                results.append(cols[-1][cols[i].index(1)])
            else:
                results.append(0)
        return results, self.objective[-1]

    def should_pivot(self):
            return len(list(filter(lambda a: a < 0, self.objective[:-1]))) > 0


run_cases = [
    (
        [-30, -60, -120],
        [
            {"co": [1, 0, 0], "val": 100},
            {"co": [0, 1, 0], "val": 25},
            {"co": [0, 0, 1], "val": 10},
            {"co": [1, 2, 3], "val": 150},
        ],
        [70.0, 25.0, 10.0, 30.0, 0, 0, 0, 0, 30.0, 0, 0, 0],
        4800.0,
    ),
]

submit_cases = run_cases + [
    (
        [-10, -50, -100],
        [
            {"co": [1, 0, 0], "val": 100},
            {"co": [0, 1, 0], "val": 50},
            {"co": [0, 0, 1], "val": 20},
            {"co": [1, 2, 3], "val": 200},
        ],
        [40.0, 50.0, 20.0, 60.0, 0, 0, 0, 0, 60.0, 0, 0, 0],
        4900.0,
    ),
]


def test(coefficients, constraints, expected_obj, expected_res):
    print("---------------------------------")
    print(f"- Coefficients:")
    print(
        f" ({coefficients[0]}*basic_subs) + ({coefficients[1]}*pro_subs) + ({coefficients[2]}*enterprise_subs) + profit = 0\n"
    )
    try:
        ss = SimplexSolver(coefficients)
        for constraint in constraints:
            print(f"Constraint:{constraint}")
            cs = []
            if constraint["co"][0] != 0:
                cs.append(f"basic_subs*{constraint['co'][0]}")
            if constraint["co"][1] != 0:
                cs.append(f"pro_subs*{constraint['co'][1]}")
            if constraint["co"][2] != 0:
                cs.append(f"enterprise_subs*{constraint['co'][2]}")
            together = " + ".join(cs)
            print(f" {together} must be less than or equal to {constraint['val']}\n")
            ss.add_constraint(constraint["co"], constraint["val"])

        ss.add_slack_variables()
        print(f"{ss}\n")
        ss.solve()
        print(f"Calling solve():\n")
        print(f"{ss}\n")
        print(f"Expected Profits {expected_res}")
        print(
            f"by selling {expected_obj[0]} basic_subs, {expected_obj[1]} pro_subs, and {expected_obj[2]} enterprise_subs\n"
        )
        cos, res = ss.get_solution_from_tableau()
        print(f"Actual Profits {res}")
        print(
            f"by selling {cos[0]} basic_subs, {cos[1]} pro_subs, and {cos[2]} enterprise_subs\n"
        )
        if cos != expected_obj or res != expected_res:
            print("Fail")
            return False
        print("Pass")
        return True
    except Exception as e:
        print(f"Error: {e}")
        print("Fail")
        return False


def main():
    passed = 0
    failed = 0
    for test_case in test_cases:
        correct = test(*test_case)
        if correct:
            passed += 1
        else:
            failed += 1
    if failed == 0:
        print("============= PASS ==============")
    else:
        print("============= FAIL ==============")
    print(f"{passed} passed, {failed} failed")


def simplex_repr(self):
    final = "\nTableau:\n\n"
    for row in self.rows:
        for i in range(len(row)):
            row[i] = float(round(row[i], 1))
        final += " " + str(row) + "\n"
    for i in range(len(self.objective)):
        self.objective[i] = float(round(self.objective[i], 1))
    final += " " + str(self.objective) + "\n"
    return final


SimplexSolver.__repr__ = simplex_repr


test_cases = submit_cases
if "__RUN__" in globals():
    test_cases = run_cases

main()
