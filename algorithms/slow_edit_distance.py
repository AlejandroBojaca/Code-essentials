def edit_distance(str1, str2):
    # Base cases
    if len(str1) == 0:
        return len(str2)
    if len(str2) == 0:
        return len(str1)
    
    # If the last characters are the same, no cost is incurred for this position
    if str1[-1] == str2[-1]:
        return edit_distance(str1[:-1], str2[:-1])
    
    # Calculate costs for insertion, deletion, and substitution
    insert = edit_distance(str1, str2[:-1])
    delete = edit_distance(str1[:-1], str2)
    substitute = edit_distance(str1[:-1], str2[:-1])
    
    # Return the minimum cost plus 1 for the current operation
    return 1 + min(insert, delete, substitute)



    


run_cases = [("docter office", "doctors office", 2), ("mcdonalds", "mc donalds", 1)]

submit_cases = run_cases + [
    ("", "", 0),
    ("spare oom", "spare room", 1),
    ("moms houzz", "moms house", 2),
    ("abracad", "abracadabra", 4),
]


def test(str1, str2, expected_output):
    print("---------------------------------")
    print(f"Detecting edit distance from: '{str1}' to '{str2}'")
    try:
        print(f"Expecting: {expected_output}")
        result = edit_distance(str1, str2)
        print(f"Actual: {result}\n")
        if result == expected_output:
            print("Pass")
            return True
        print("Fail")
        return False
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


test_cases = submit_cases
if "__RUN__" in globals():
    test_cases = run_cases

main()
