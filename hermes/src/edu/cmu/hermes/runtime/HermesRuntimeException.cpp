/* 
 * File:   HermesRuntimeException.cpp
 * Author: rmartins
 * 
 * Created on April 28, 2013, 11:37 AM
 */

#include "HermesRuntimeException.h"

const char* HermesRuntimeException::GENERAL_ERROR = "General Error";



HermesRuntimeException::HermesRuntimeException(const char* exception) : m_messageString(exception) {


}

HermesRuntimeException::HermesRuntimeException(const HermesRuntimeException& c) : m_messageString(c.m_messageString) {
}

HermesRuntimeException::~HermesRuntimeException() {
}


