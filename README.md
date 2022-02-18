# Path
 learning pathing algo


After getting the release:
	right clic on  "Path.uproject"
	-> generate visual studio project files
	
	then double click on "Path.uproject" to lunch the unreal project => he ask you to rebuild project you say yes
	You can also double click on the "Path.sln" to open sources files


When the project is open on unreal 4:
	if you don't see the map and all the actors:
		-> go on the file (left-down) -> content -> map -> double click on map
here you can see:
	- the main character you can control with ZQSD
	- the npc (enemie) who look like a cone
	- and some point who represent the circuit who can be follow.

SELECT A BEHAVIOUR:
	click on the npc (the cone) 
	at right try to find the "Steering Param", here you can fix different things:
		- Mass : mass of the object
		- Max force
		- Max speed
		- Target (who the npc gonna follow) useles if you use a circuit, or one way strategy
		- Strategy you want to use with this npc 
		- Current circuit, to fix the list of the target if you want to do a circuit

you can place different actor (BP_npc or NP_Circuit_CheckPoint), you find them on content/Blueprint
don't miss to clic on the npc when you place one to fix he's parameter ( target, strategy etc) 
and also fix their Location Z parameter to 88 like others to be at the same height. 

How to do a circuit :
	 Place different "BP_Circuit_CheckPoint" to design the parcour. then clic on your actor/npc, fix the strategy to circuit,
	and add element to the "Current Circuit" parameter. Add the waypoint you just add in the order you want.  
					

