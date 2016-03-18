import io
# Read file an store every number from Start of file to EOF in data.list
# get dimmensions of the ppm file
# seize of picture
# class grid:
#     def __init__(self):
#         self.width = 0
#         self.width = 0
class rgb:
    def __init__(self):
        self.a = 0
        self.b = 0
    
s = rgb()
s.a = 10
# print(s.a+2)

with open('samp1.ppm', 'r') as ppm:
    data = ppm.read()
    values = data.split()
#        print(values[1]);
    num_row = int(values[1])
    num_col = int(values[2])
#     print("num_row,num_col", num_row,num_col)
    offset=4;
    totat_elements_grid=num_row*num_col
#     print(type(data))
#     print(totat_elements_grid)
    totat_elements_grid=(totat_elements_grid*3)+offset
    
    row=[]
    for i in range(4,totat_elements_grid,3):
        rgb=(int(values[i]), int(values[i+1]), int(values[i+2]))
        row.append(rgb) 
        print(i,"", rgb)
    
#Now every rgb is stored in rows array
#     print(row)
#create grid]
    print ("values in row ", row)
    k=0
    it=0;
#     grid = [ [(0,0,0)] * num_col ] * num_row
    grid=[[(0,0,0)]*5 for i in range(4)]
    grid[0][0]=(2,2,2)
    print("--->",grid)
    print ("empty grid",grid)
    for i in range(0,num_row):
        for j in range(0,num_col):
            grid[i][j]=row[k]
#             print("grid[i][j]", i,j,k,"", grid[i][j],"row_k ",row[k])
            print(grid)
        
            k+=1
#     print("end of grid iteration")
#     print("grid[0][0]",grid[0][0])
#     print(grid)
#     # Functions Start
    def width(grid):
        w=len(grid[0])
        print(w)
        return w
    
    def height(grid):
        rows = len(grid)
        print(rows)
        return rows
        
    
    width(grid)
    height(grid)
    
    def energy_at(grid,r,c):# Given a grid of RGB triplets, calculate the energy gradient at that location. 2
    #Case one if cur node is an interior node
        w=width(grid)
        h=height(grid)
        if (( w>c) and (h > r)): 
            print("inside node case",grid[r][c])
#     width(grid)
#     height(grid)

energy_at(grid, 1, 1)


    


#     def width(grid): Given a grid, determine how wide it is (how many columns there are). You may assume it’s rectangular (you don’t have to check every single row’s width).
# 2. def height(grid): Given a grid, determine how tall it is (how many rows there are). You may assume it’s rectangular.
# 3. def energy_at(grid,r,c): Given a grid of RGB triplets, calculate the energy gradient at that location.
    
#     rgb=(int(values[i+1]), int(values[i+2]), int(values[i+2]))
#     print(rgb)
#     row=[]
#     while(i<=totat_elements_grid):
#         rgb=(int(values[i+1]), int(values[i+2]), int(values[i+2]))
#         row.append(rgb)
#         i+=1  
#         
     
#     pi_tuple = (3, 1, 4, 1, 5, 9)
#     print(pi_tuple[0])
    #print(numb_elements_grid)
# Note: starting at values 3 RBS triples beging


#create a grid= double list. Every 3 numbers its a triple

# for i in range(num_row):
#     for j in range(num_col):    

