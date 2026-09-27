# GitHub and Version Control
Throughout the design cycle of our solar vehicles, many people work on many parts of the car across different times and locations. Naively, we could just have everyone come to a single point (e.g. Cory Hall) to work on stuff. However, finding scheduling overlaps and having everyone in the same place is very difficult. Also, if we use different computers, how do we merge changes across different files?

## The Solution: GitHub
Github is an online cloud-based platform where people store, share, and work together on computer code. It is also a tool for us to use for
version control. For CalSol, we store all of our hardware and firmware files on GitHub, which lets us work on the car no matter where we are! For this reading, we will be heavily referencing the CS61B HW01 Setup. Please first read [this section](https://sp26.datastructur.es/homeworks/hw01/#tools-overview-git) on Git overview.

## Action Item 🎯: Setup GitHub
1. Create a GitHub account at [here](https://github.com/) if you don't already have one. We recommend **using your personal email**, and adding your Berkeley account later for student benefits.
2. Install Git/GitBash on your system. You can follow the CS61B HW01 Task 1 instructions [here](https://sp26.datastructur.es/homeworks/hw01/#task-1-install-git).
3. Set up your Git! To connect your GitHub account to your terminal you can follow the CS61B HW01 Task 3 instructions [here](https://sp26.datastructur.es/homeworks/hw01/#task-3-set-up-git).
4. Reach out to the Electrical PMs on Slack with the email you used to create your account so we can add you to the club organization.
5. Clone **this** GitHub repository so that you access to the exercises and other content. You can use the following in your terminal commands to do so, and you can find more specific details from the CS61B HW01 Task 5 instructions [here](https://sp26.datastructur.es/homeworks/hw01/#task-5-cloning-repositories).

```
cd <folder you want to clone the repository folder in>
git clone https://github.com/CalSol/Fa26-CalSol-Firmware-Training
```

_GitHub also provides a Graphical User Interface (GUI) through GitHub Desktop, which abstracts away the CLI (for better or worse). You can download GitHub Desktop [here](https://desktop.github.com/download/)._

## Appendix: Cloning a Repository
To clone a repository is to download a complete local copy of a project, including all its files, branches, and version history.

Here is a youtube video on how to do that in GitHub Desktop: https://www.youtube.com/watch?v=PoZNIbs_wx8

Here is a youtube video on how to do that using Git Bash: https://www.youtube.com/watch?v=ZFFtMyOFPe8
