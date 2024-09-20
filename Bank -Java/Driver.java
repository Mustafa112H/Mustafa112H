//Heba Mustafa 1221916
//Lab 4
//Lecture Section 3
package proj_1221916_s4;

import java.util.*;
public class Driver {
	 public static void main(String[] args) {
	        String val1 = "Very Nice Final Exam Comp 2310";
	        String a = "Comp", b = "Exam", c = "Very", d = "Nice";
	        String val2 = "";
	        for (int i = 0; i < 2; i++) {
	            val2 = replaceAllCustom(val1, a, b);
	            a = c;
	            b = d;
	        }
	        System.out.println(val2);
	    }

	    public static String replaceAllCustom(String input, String target, String replacement) {
	        StringBuilder result = new StringBuilder();     
	        int index = input.indexOf(target);
	        int lastIndex = 0;
	   
	        while (index != -1) {
	            result.append(input, lastIndex, index);
	            result.append(target);
	            lastIndex = index + target.length();
	            index = input.indexOf(target, lastIndex);
	        }
	        result.append(input, lastIndex, input.length());
	        return result.toString();
	    }
	}

