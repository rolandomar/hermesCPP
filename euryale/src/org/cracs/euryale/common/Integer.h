/*
 *  Copyright 2012 Rolando Martins, CRACS & INESC-TEC, DCC/FCUP
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *   
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 */
/* 
 * File:   Integer.h
 * Author: Rolando Martins (rolando.martins@gmail.com)
 *
 * Created on May 6, 2010, 5:10 PM
 */

#ifndef INTEGER_H
#define	INTEGER_H

#include <euryale/Types.h>
#include <sstream>
#include <euryale/common/Object.h>


class Integer: public Object {
public:
    Integer();
    Integer(int i):m_i(i){
        
    }
    virtual ~Integer();

    static int parseInt(String str, int base);
    static int parseInt(char* s, int base);
    static int parseInt(const char* s, int base);

    static Long parseLong(String str, int base);
    static Long parseLong(char* s, int base);
    static Long parseLong(const char* s, int base);

    static const char digits[];

    static String toHexString(int i) {
        return toUnsignedString(i, 4);
    }

    static String toUnsignedString(int i, int shift);
    static String toUnsignedString(int i);

    template <class T>
    inline static String numberToString(const T& t) {
        std::stringstream ss;
        ss << t;
        String str(ss.str().c_str());
        return str;
    }

    template <class T>
    inline static T stringToNumber(const String& t) {
        std::string str(t.c_str());
        std::istringstream ss(str);        
        T result;
        return ss >> result ? result : -1;
    }
    
    int getInt(){
        return m_i;
    }
    
    virtual const char* objectID() const {
        return "120938120938282aa123";
    }
protected:
    int m_i;

};

#endif	/* INTEGER_H */

