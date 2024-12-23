from property import create_prpt, PrptClass


ary = [
    create_prpt("QString", 'name'),
    create_prpt("QString", 'data')
]

enumClasss = []

prptClass = PrptClass("Dropdownlist", ary, enumClasss)
