def min_edit_distance(s1, s2):
    len1 = len(s1)
    len2 = len(s2)

    # Initializăm matricea de distanțe
    d = [[0 for j in range(len2 + 1)] for i in range(len1 + 1)]

    # Inițializăm primele rânduri și coloane
    for i in range(len1 + 1):
        d[i][0] = i
    for j in range(len2 + 1):
        d[0][j] = j

    # Calculăm distanța minimă folosind algoritmul Levenshtein
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            cost = 0 if s1[i - 1] == s2[j - 1] else 1
            d[i][j] = min(d[i - 1][j] + 1,     # ștergere
                         d[i][j - 1] + 1,      # inserare
                         d[i - 1][j - 1] + cost)  # substituire

    return d[len1][len2]

def main():
    try:
        with open("input.txt", "r") as file:
            rule = file.readline().strip()
            fragment = file.readline().strip()

        distance = min_edit_distance(fragment, rule)
        print(f"Numarul minim de operatii necesare pentru a corecta fragmentul de cod: {distance}")

    except FileNotFoundError:
        print("Nu s-a putut deschide fisierul input.txt")

if __name__ == "__main__":
    main()