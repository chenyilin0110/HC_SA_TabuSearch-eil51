DEL HC-eil51*.txt SA-eil51*.txt Tabu_search-eil51*.txt

for %%d in (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30) do (	
	HC-eil51.exe >> HC-eil51-%%d.txt
	SA-eil51.exe >> SA-eil51-%%d.txt
	Tabu_search-eil51.exe >> Tabu_search-eil51-%%d.txt
)
pause