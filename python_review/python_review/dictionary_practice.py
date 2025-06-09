 labor_dictionary = {
    "Wang Lihang": {"department": "Technology", "Salary": 3000, "Level": 1},
    "Zhou Jielun": {"department": "Market", "Salary": 5000, "Level": 2},
    "Lin Junjie": {"department": "Market", "Salary": 7000, "Level": 3},
    "Zhang Xueyou": {"department": "Technology", "Salary": 4000, "Level": 1},
    "Liu Dehua": {"department": "Market", "Salary": 6000, "Level": 2}
}
print(labor_dictionary)
for key in labor_dictionary:
    if labor_dictionary[key]["Level"] <= 1:
        labor_dictionary[key]["Salary"] += 1000
        labor_dictionary[key]["Level"] += 1

print(labor_dictionary)