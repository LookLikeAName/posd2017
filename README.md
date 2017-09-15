# myProject
Use the makefile to compile the c++ file and run the test with [googleTest](https://github.com/google/googletest).

Follow the steps to complete settings. You need to setup the compile environment on your PC to run the project with test, and add webhook for your repository that can trigger [CI server](http://140.124.181.114:8080/) to do the building and running automated test.

This project is only used to create the environment, you should clean it when HW1.

#### Updata
 * Wed Sep 13 2017 14:12:35
 
 About \<studentId\>, you should replace whole brackets not just "studentId". That is ok on email subject , but you should be careful the webhook.
  
  ```
  Good:
  http://140.124.181.114:8080/buildByToken/build?job=1055980XX&token=1055980XX
  
  Bad:
  http://140.124.181.114:8080/buildByToken/build?job=<1055980XX>&token=<1055980XX>
  ```
And about your own repository, if you want to test your CI job is setup or not: init your repository and place this project's file, commit and push a simple change, and go to CI server to check the job result.

## 1. How to set up everything on your PC

#### Prerequisites

* [Windows 10](https://blog.gtwang.org/windows/how-to-get-ubuntu-and-bash-running-on-windows-10/)

### Install GoogleTest in different platforms

* [Windows 10 / Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
* [Mac](https://gist.github.com/massenz/41bb2c8375294f4d9927)
* [Windows 7](https://github.com/iat-cener/tonatiuh/wiki/Installing-Google-Test-For-Windows)

### Running the tests
```shell
cd <your/project/path>
make
./exp
```

After run the exp file, you should get the result like that: 
![Imgur](https://i.imgur.com/BEPHs86.png)


## 2. How to set up everything for CI server

You already have an account on [the CI server](http://140.124.181.114:8080/). 
Username and password is your student id, so your need to reset password first.
![Imgur](https://i.imgur.com/GoYBxXp.png)

### Create a new repository
https://github.com/new

Name your repository whatever you want, and place this project's file to your own repository(exclude .git folder).

### Add WebHook to repository

On repository page -> Settings -> Webhooks -> Add webhook -> set Payload URL :
```
http://140.124.181.114:8080/buildByToken/build?job=<studentId>&token=<studentId>
```
And it should show the green tick.

![Imgur](https://i.imgur.com/wbjjetV.png)

### Email your repository url to TA
Email to posd2017f@gmail.com. Just need subject, no content required.

```
Subject: <studentId>, <repositoryURL>
```
![Imgur](https://i.imgur.com/dEkZk1Q.png)


### After email
Wait TA for setting, your CI job will be triggered to run test after every push.

## Done

If you have some problems that you really don't know why and how to solve it, email us: posd2017f@gmail.com or come to 1321 in office hours (Fri. 2pm to 4pm).
