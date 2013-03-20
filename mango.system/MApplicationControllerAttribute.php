<?php

	/*
	 * Copyright (c) 2011 Movinpixel Ltd. All rights reserved.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 * 3. Neither the name of the company nor the names of its contributors
	 *    may be used to endorse or promote products derived from this software
	 *    without specific prior written permission.
	 *
	 * THIS SOFTWARE IS PROVIDED BY MOVINPIXEL AND ITS CONTRIBUTORS ``AS IS'' AND
	 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	 * ARE DISCLAIMED.  IN NO EVENT SHALL MOVINPIXEL OR ITS CONTRIBUTORS BE LIABLE
	 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	 * SUCH DAMAGE.
	 */
	
	package('mango.system');
	
	/**
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @package mango.system
	 *
	 */
	abstract class MApplicationControllerAttribute extends MObject {
		
		const StringType = 0;
		const IntegerType = 1;
		const FloatType = 2;
		const BooleanType = 3;
		const DateType = 4;
		const BinaryType = 5;
		const ArrayType = 6;
		const DictionaryType = 7;
		
		protected $name;
		protected $type;
		protected $required;
		
		public function __construct(MString $name, $type, $required = true) {
			MAssertTypes('int', $type, 'bool', $required);
			parent::__construct();
			
			$this->name = $name;
			$this->type = $type;
			$this->required = $required;
		}
		
		/******************** Properties ********************/
		
		/**
		 * @return MString
		 */
		public function name() {
			return $this->name;
		}
		
		/**
		 * @return int
		 */
		public function type() {
			return $this->type;
		}
		
		/**
		 * @return bool
		 */
		public function required() {
			return $this->required;
		}
		
		/******************** Methods ********************/
		
		/**
		 * @return MString
		 */
		public function expectedDataType() {
			if ($this->type() == MApplicationControllerField::StringType) {
				return S("String");
			} else if ($this->type() == MApplicationControllerField::IntegerType) {
				return S("Integer");
			} else if ($this->type() == MApplicationControllerField::FloatType) {
				return S("Float");
			} else if ($this->type() == MApplicationControllerField::BooleanType) {
				return S("Boolean");
			} else if ($this->type() == MApplicationControllerField::DateType) {
				return S("Date");
			} else if ($this->type() == MApplicationControllerField::BinaryType) {
				return S("Binary");
			} else if ($this->type() == MApplicationControllerField::ArrayType) {
				return S("Array");
			} else if ($this->type() == MApplicationControllerField::DictionaryType) {
				return S("Dictionary"); 
			} else {
				return S("Unknown");
			}
		}
		
		/******************** MObject ********************/
		
		/**
		 *
		 */
		public function toString() {
			return Sf("%s(%s)", $this->className(), $this->name());
		}
		
	}

?>