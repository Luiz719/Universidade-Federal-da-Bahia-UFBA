import csv

with open('resultados.txt') as file:
    # open the file in the write mode

    use = 0
    alloc = 0
    
    
    with open('tabela.csv', 'w') as f:
        writer = csv.writer(f)
        for row in file:
            row = [r.replace("\n","").replace(" ", "") for r in row.split()]

            try:
                use += int(row[0])
                alloc += int(row[3]) * int(row[2])
            except:
                continue
            
            # write a row to the csv file
            writer.writerow(row)


print("Alpha-médio:", use/alloc)
