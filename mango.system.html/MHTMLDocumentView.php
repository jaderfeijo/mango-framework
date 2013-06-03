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
	 
	package('mango.system.html');
	
	import('mango.system.*');
	
	/**
	 * 
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @license MIT
	 *
	 * @package mango.system.html
	 *
	 */
	class MHTMLDocumentView extends MHTMLElementView {
		
		//
		// ************************************************************
		//
		
		protected $bodyElement;
		protected $titleElement;
		
		protected $headElement;
		
		/**
		 * 
		 *
		 * @return MHTMLDocumentView
		 */
		public function __construct(MString $title = null) {
			parent::__construct(S("html"));
			
			$this->bodyElement = new MHTMLElementView(S("body"));
			$this->titleElement = new MHTMLElementView(S("title"), $title);
			
			$this->headElement = new MHTMLElementView(S("head"));
			$this->headElement->addSubview($this->titleElement);
			
			$this->addSubview($this->headElement);
			$this->addSubview($this->bodyElement);
		}
		
		/******************** Protected ********************/
		
		/**
		 * @return MArray
		 */
		protected function _subviews() {
			return parent::subviews();
		}
		
		/**
		 * @return void
		 */
		protected function _addSubview(MView $view) {
			parent::addSubview($view);
		}
		
		/**
		 * @return void
		 */
		protected function _removeSubview(MView $view) {
			parent::removeSubview($view);
		}
		
		/**
		 * @return void
		 */
		protected function _removeAllSubviews() {
			parent::removeAllSubviews();
		}
		
		/******************** Properties ********************/
		
		/**
		 * @return MHTMLElementView
		 */
		public function headElement() {
			return $this->headElement;
		}
		
		/**
		 *
		 *
		 * @return MArray
		 */
		public function headElements() {
			return $this->headElement->subviews();
		}
		
		/**
		 *
		 *
		 * @return void
		 */
		public function addHeadElement(MHTMLElementView $element) {
			$this->headElement->addSubview($element);
		}
		
		/**
		 *
		 *
		 * @return void
		 */
		public function removeHeadElement(MHTMLElementView $element) {
			$this->headElement->removeSubview($element);
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function setTitle(MString $title) {
			$this->titleElement->setText($title);
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function title() {
			return $this->titleElement->text();
		}
		
		/******************** MView Methods ********************/
		
		/**
		 *
		 */
		public function subviews() {
			return $this->bodyElement->subviews();
		}
		
		/**
		 *
		 */
		public function addSubview(MView $view) {
			$this->bodyElement->addSubview($view);
		}
		
		/**
		 *
		 */
		public function removeSubview(MView $view) {
			$this->bodyElement->removeSubview($view);
		}
		
		/**
		 *
		 */
		public function removeAllSubviews() {
			$this->bodyElement->removeAllSubviews();
		}
		
	}

?>