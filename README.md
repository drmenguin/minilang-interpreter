# MiniLang Compiler

This compiler is a programming assignment for [CPS2000: Compiler Theory and Practice](https://www.um.edu.mt/courses/studyunit/CPS2000), a course forming part of my B.Sc. in Mathematics and Computer Science.

The following is a valid program written in MiniLang.

    def funcSquare(x : real) : real {
        return x∗x;
    }

    def funcGreaterThan(x : real, y : real) : bool {
        var ans : bool = true;
        if (y > x) {
           set ans = false;
        }
        return ans;
    }

    var x : real = 2.4 ;
    var y : real = funcSquare(2.5);
    print y;                                       // 6.25
    print funcGreaterThan(x, 2.3);                 // true
    print funcGreaterThan(x, funcSquare(1.555));   // false
   
