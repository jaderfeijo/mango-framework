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
	
	import('mango.system.*');
	
	/**
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @package mango.system
	 *
	 */
	class MApplicationControllerAcceptedMethod extends MObject {
		
		protected $method;
		protected $contentTypes;
		protected $parameters;
		protected $fields;
		
		public function __construct(MString $method) {
			parent::__construct();
			
			$this->method = $method;
			$this->contentTypes = new MMutableArray();
			$this->parameters = new MMutableArray();
			$this->fields = new MMutableArray();
		}
		
		/******************** Properties ********************/
		
		/**
		 * @return MString
		 */
		public function method() {
			return $this->method;
		}
		
		/**
		 * @return MArray
		 */
		public function contentTypes() {
			return $this->contentTypes;
		}
		
		/**
		 * @return MArray
		 */
		public function parameters() {
			return $this->parameters;
		}
		
		/**
		 * @return MArray
		 */
		public function fields() {
			return $this->fields;
		}
		
		/******************** Methods ********************/
		
		/**
		 * @return void
		 */
		public function addContentType(MString $contentType) {
			$this->contentTypes->addObject($contentType);
		}
		
		/**
		 * @return void
		 */
		public function removeContentType(MString $contentType) {
			$this->contentTypes->removeObject($contentType);
		}
		
		/**
		 * @return void
		 */
		public function removeAllContentTypes() {
			$this->contentTypes->removeAllObjects();
		}
		
		/**
		 * @return void
		 */
		public function addParameter(MApplicationControllerParameter $parameter) {
			$this->parameters->addObject($parameter);
		}
		
		/**
		 * @return void
		 */
		public function removeParameter(MApplicationControllerParameter $parameter) {
			$this->parameters->removeObject($parameter);
		}
		
		/**
		 * @return void
		 */
		public function removeAllParameters() {
			$this->parameters->removeAllObjects();
		}
		
		/**
		 * @return void
		 */
		public function addField(MApplicationControllerField $field) {
			$this->fields->addObject($field);
		}
		
		/**
		 * @return void
		 */
		public function removeField(MApplicationControllerField $field) {
			$this->fields->removeObject($this);
		}
		
		/**
		 * @return void
		 */
		public function removeAllFields() {
			$this->fields->removeAllObjects();
		}
		
		/**
		 * @return MApplicationControllerParameter
		 */
		public function parameterWithName(MString $name) {
			foreach ($this->parameters()->toArray() as $parameter) {
				if ($parameter->name()->equals($name)) {
					return $parameter;
				}
			}
			return null;
		}
		
		/**
		 * @return MApplicationControllerField
		 */
		public function fieldWithName(MString $name) {
			foreach ($this->fields()->toArray() as $field) {
				if ($field->name()->equals($name)) {
					return $field;
				}
			}
			return null;
		}
		
	}

?>