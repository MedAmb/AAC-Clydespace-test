# Build Instruction

1 - Download docker image with gtest/gmock pre-installed.
```console
docker pull srzzumix/googletest
```

2 - Clone project.
```console
git clone https://github.com/MedAmb/AAC-Clydespace-test.git
```

3 - Run the docker with the project
```console
docker run -it -v ./AAC-Clydespace-test:/project --name Coding-test srzzumix/googletest
```

4 - Generate and build the project
```console
cmake -B /project/build && cmake --build /project/build
```

4 - (Optional): Run the unit test
```console
/project/build/test/unit_test_lis3mdl_driver
```