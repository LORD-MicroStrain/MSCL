/*
This file is part of Natural Docs, which is Copyright © 2003-2018 Code Clear LLC.
Natural Docs is licensed under version 3 of the GNU Affero General Public
License (AGPL).  Refer to License.txt or www.naturaldocs.org for the
complete details.

This file may be distributed with documentation files generated by Natural Docs.
Such documentation is not covered by Natural Docs' copyright and licensing,
and may have its own copyright and distribution terms as decided by its author.
*/

"use strict";var NDCore=new function(){this.GetElementsByClassName=function(baseElement,className,tagHint){if(baseElement.getElementsByClassName){return baseElement.getElementsByClassName(className);}if(!tagHint){tagHint="*";}var tagArray=baseElement.getElementsByTagName(tagHint);var matchArray=new Array();var tagIndex=0;var matchIndex=0;while(tagIndex<tagArray.length){if(this.HasClass(tagArray[tagIndex],className)){matchArray[matchIndex]=tagArray[tagIndex];matchIndex++;}tagIndex++;}return matchArray;};this.HasClass=function(element,targetClassName){if(element.className==undefined){return false;}var index=element.className.indexOf(targetClassName);if(index!=-1){if((index==0||element.className.charAt(index-1)==' ')&&(index+targetClassName.length==element.className.length||element.className.charAt(index+targetClassName.length)==' ')){return true;}}return false;};this.AddClass=function(element,newClassName){if(element.className==undefined){element.className=newClassName;return;}var index=element.className.indexOf(newClassName);if(index!=-1){if((index==0||element.className.charAt(index-1)==' ')&&(index+newClassName.length==element.className.length||element.className.charAt(index+newClassName.length)==' ')){return;}}if(element.className.length==0){element.className=newClassName;}else{element.className+=" "+newClassName;}};this.RemoveClass=function(element,targetClassName){if(element.className==undefined){return;}var index=element.className.indexOf(targetClassName);while(index!=-1){if((index==0||element.className.charAt(index-1)==' ')&&(index+targetClassName.length==element.className.length||element.className.charAt(index+targetClassName.length)==' ')){var newClassName="";if(index>0){newClassName+=element.className.substr(0,index);}if(index+targetClassName.length!=element.className.length){newClassName+=element.className.substr(index+targetClassName.length);}element.className=newClassName;return;}index=element.className.indexOf(targetClassName,index+1);}};this.LoadJavaScript=function(path,id){var script=document.createElement("script");script.src=path;script.type="text/javascript";if(id!=undefined){script.id=id;}document.getElementsByTagName("head")[0].appendChild(script);};this.RemoveScriptElement=function(id){var script=document.getElementById(id);if(this.IEVersion()==6){setTimeout(function(){script.parentNode.removeChild(script);},1);}else{script.parentNode.removeChild(script);}};this.WindowClientWidth=function(){var width=window.innerWidth;if(width===undefined){width=document.documentElement.clientWidth;}return width;};this.WindowClientHeight=function(){var height=window.innerHeight;if(height===undefined){height=document.documentElement.clientHeight;}return height;};this.SetToAbsolutePosition=function(element,x,y,width,height){if(x!=undefined&&element.offsetLeft!=x){element.style.left=x+"px";}if(y!=undefined&&element.offsetTop!=y){element.style.top=y+"px";}if(width!=undefined&&element.offsetWidth!=width){if(!this.pxRegex.test(element.style.width)){element.style.width=width+"px";if(element.offsetWidth!=width){var adjustment=width-element.offsetWidth;element.style.width=(width+adjustment)+"px";}}else{var styleWidth=RegExp.$1;var adjustment=styleWidth-element.offsetWidth;element.style.width=(width+adjustment)+"px";}}if(height!=undefined&&element.offsetHeight!=height){if(!this.pxRegex.test(element.style.height)){element.style.height=height+"px";if(element.offsetHeight!=height){var adjustment=height-element.offsetHeight;element.style.height=(height+adjustment)+"px";}}else{var styleHeight=RegExp.$1;var adjustment=styleHeight-element.offsetHeight;element.style.height=(height+adjustment)+"px";}}};this.GetFullOffsets=function(element){var result={offsetTop:element.offsetTop,offsetLeft:element.offsetLeft};element=element.offsetParent;while(element!=undefined&&element.nodeName!="BODY"){result.offsetTop+=element.offsetTop;result.offsetLeft+=element.offsetLeft;element=element.offsetParent;}return result;};this.NormalizeHash=function(hashString){if(hashString==undefined){return"";}if(hashString.charAt(0)=="#"){hashString=hashString.substr(1);}hashString=decodeURI(hashString);return hashString;};this.IsIE=function(){return(navigator.userAgent.indexOf("MSIE")!=-1||navigator.userAgent.indexOf("Trident")!=-1);};this.IEVersion=function(){var ieIndex=navigator.userAgent.indexOf("MSIE");if(ieIndex!=-1){ieIndex+=5;}else{ieIndex=navigator.userAgent.indexOf("Trident");if(ieIndex!=-1){ieIndex=navigator.userAgent.indexOf("rv:");if(ieIndex!=-1){ieIndex+=3;}}}if(ieIndex!=-1){return parseInt(navigator.userAgent.substr(ieIndex));}else{return undefined;}};this.AddIEClassesToBody=function(){var ieVersion=this.IEVersion();if(ieVersion!=undefined){this.AddClass(document.body,"IE");if(ieVersion>=6&&ieVersion<=8){this.AddClass(document.body,"IE"+ieVersion);}}};this.SupportsOnInput=function(){if(this.IEVersion()==9){return false;}else{return(window.oninput!==undefined);}};this.ChangePrototypeToNarrowForm=function(prototype){var newPrototype=document.createElement("div");newPrototype.id=prototype.id;newPrototype.className=prototype.className;this.RemoveClass(newPrototype,"WideForm");this.AddClass(newPrototype,"NarrowForm");var prePrototypeLines=NDCore.GetElementsByClassName(prototype,"PPrePrototypeLine","div");for(var i=0;i<prePrototypeLines.length;i++){newPrototype.appendChild(prePrototypeLines[i].cloneNode(true));}var table=prototype.getElementsByTagName("table")[0];var newTable=document.createElement("table");newPrototype.appendChild(newTable);var newRow=newTable.insertRow(-1);newRow.appendChild(table.rows[0].cells[0].cloneNode(true));newRow=newTable.insertRow(-1);newRow.appendChild(table.rows[0].cells[1].cloneNode(true));newRow=newTable.insertRow(-1);newRow.appendChild(table.rows[0].cells[2].cloneNode(true));var postPrototypeLines=NDCore.GetElementsByClassName(prototype,"PPostPrototypeLine","div");for(var i=0;i<postPrototypeLines.length;i++){newPrototype.appendChild(postPrototypeLines[i].cloneNode(true));}prototype.parentNode.replaceChild(newPrototype,prototype);};this.ChangePrototypeToWideForm=function(prototype){var newPrototype=document.createElement("div");newPrototype.id=prototype.id;newPrototype.className=prototype.className;this.RemoveClass(newPrototype,"NarrowForm");this.AddClass(newPrototype,"WideForm");var prePrototypeLines=NDCore.GetElementsByClassName(prototype,"PPrePrototypeLine","div");for(var i=0;i<prePrototypeLines.length;i++){newPrototype.appendChild(prePrototypeLines[i].cloneNode(true));}var table=prototype.getElementsByTagName("table")[0];var newTable=document.createElement("table");newPrototype.appendChild(newTable);var newRow=newTable.insertRow(-1);newRow.appendChild(table.rows[0].cells[0].cloneNode(true));newRow.appendChild(table.rows[1].cells[0].cloneNode(true));newRow.appendChild(table.rows[2].cells[0].cloneNode(true));var postPrototypeLines=NDCore.GetElementsByClassName(prototype,"PPostPrototypeLine","div");for(var i=0;i<postPrototypeLines.length;i++){newPrototype.appendChild(postPrototypeLines[i].cloneNode(true));}prototype.parentNode.replaceChild(newPrototype,prototype);};this.GetComputedStyle=function(element,style){var result=element.style[style];if(result!=""){return result;}if(window.getComputedStyle){return window.getComputedStyle(element,"")[style];}else if(element.currentStyle){return element.currentStyle[style];}else{return undefined;}};this.GetComputedPixelWidth=function(element,style){var result=this.GetComputedStyle(element,style);if(this.pxRegex.test(result)){return parseInt(RegExp.$1,10);}else{return 0;}};this.pxRegex=/^([0-9]+)px$/i;};String.prototype.StartsWith=function(other){if(other===undefined){return false;}return(this.length>=other.length&&this.substr(0,other.length)==other);};String.prototype.EntityDecode=function(){var output=this;output=output.replace(/&lt;/g,"<");output=output.replace(/&gt;/g,">");output=output.replace(/&quot;/g,"\"");output=output.replace(/&amp;/g,"&");return output;};function NDLocation(hashString){this.Constructor=function(hashString){this.hashString=NDCore.NormalizeHash(hashString);if(this.hashString.match(/^File[0-9]*:/)!=null){this.type="File";this.SplitPathAndMember();this.AddFileURLs();}else if(this.hashString.match(/^[A-Z]+Class:/i)!=null){this.type="Class";this.SplitPathAndMember();this.AddClassURLs();}else if(this.hashString.substr(0,9).toLowerCase()=="database:"){this.type="Database";this.SplitPathAndMember();this.AddDatabaseURLs();}else{this.type="Home";this.AddHomeURLs();}};this.SplitPathAndMember=function(){var pathSeparator=this.hashString.indexOf(':');var memberSeparator=this.hashString.indexOf(':',pathSeparator+1);if(memberSeparator==-1){this.path=this.hashString;}else{this.path=this.hashString.substr(0,memberSeparator);this.member=this.hashString.substr(memberSeparator+1);if(this.member==""){this.member=undefined;}}};this.AddHomeURLs=function(){this.contentPage="other/home.html";};this.AddFileURLs=function(){var pathPrefix=this.path.match(/^File([0-9]*):/);var basePath="files"+pathPrefix[1]+"/"+this.path.substr(pathPrefix[0].length);var lastSeparator=basePath.lastIndexOf('/');var filename=basePath.substr(lastSeparator+1);filename=filename.replace(/\./g,'-');basePath=basePath.substr(0,lastSeparator+1)+filename;this.contentPage=basePath+".html";this.summaryFile=basePath+"-Summary.js";this.summaryTTFile=basePath+"-SummaryToolTips.js";if(this.member!=undefined){this.contentPage+='#'+this.member;}};this.AddClassURLs=function(){var pathPrefix=this.path.match(/^([A-Z]+)Class:/i);var basePath="classes/"+pathPrefix[1]+"/"+this.path.substr(pathPrefix[0].length);basePath=basePath.replace(/\.|::/g,"/");this.contentPage=basePath+".html";this.summaryFile=basePath+"-Summary.js";this.summaryTTFile=basePath+"-SummaryToolTips.js";if(this.member!=undefined){this.contentPage+='#'+this.member;}};this.AddDatabaseURLs=function(){var basePath="database/"+this.path.substr(9);basePath=basePath.replace(/\./g,"/");this.contentPage=basePath+".html";this.summaryFile=basePath+"-Summary.js";this.summaryTTFile=basePath+"-SummaryToolTips.js";if(this.member!=undefined){this.contentPage+='#'+this.member;}};this.Constructor(hashString);};if(!Array.prototype.indexOf){Array.prototype.indexOf=function(searchElement){"use strict";if(this==null){throw new TypeError();}var n,k,t=Object(this),len=t.length>>>0;if(len===0){return-1;}n=0;if(arguments.length>1){n=Number(arguments[1]);if(n!=n){n=0;}else if(n!=0&&n!=Infinity&&n!=-Infinity){n=(n>0||-1)*Math.floor(Math.abs(n));}}if(n>=len){return-1;}for(k=n>=0?n:Math.max(len-Math.abs(n),0);k<len;k++){if(k in t&&t[k]===searchElement){return k;}}return-1;};}