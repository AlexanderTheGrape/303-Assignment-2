# 303-Assignment-2
Pacemaker Project

How to use:

Download the repository onto the hard drive of the computer, which must be running windows. Extract the folder onto the D: drive.
Open up the Quartus program, and upon the prompt to choose a project, locate the cs303_assignment2.qpf file in the D:\303-Assignment-2\Lab___export\Prebuilt_Nios directory.
Next, connect the power adapter to the Altera board as well as the programming cable to the first slot (the closest to the corner). Program the board in Quartus with the cs303.sof file, found in the D:\303-Assignment-2\Lab___export\Prebuilt_Nios directory.
Next, open up the Nios II Software Built Tool for Eclipse, found in the tools dropdown menu. Use the D:\303-Assignment-2\Lab___export\Prebuilt_Nios\software directory.
Once Eclipse opens, right-click the project in project explorer, hover over “Run As”, and click “3 Nios II Hardware”. Once loaded, scroll to the left and click “refresh”, you should then be able to program the Nios II processor. 
Set switch 0 to low (0) for mode 1, and set it to high (1) for mode 2.
Press button 0 to simulate a natural ventricular beat, and press button 1 to simulate a natural atrial beat.
