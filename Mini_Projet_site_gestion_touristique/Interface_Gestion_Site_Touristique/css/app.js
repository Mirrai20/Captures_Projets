var map = document.querySelector('#map')
var paths = map.querySelectorAll('.map_image a')
var links = map.querySelectorAll('.map_list a')

if(NodeList.prototype.forEach===undefined){
	NodeList.prototype.forEach=function(callback){
		[].forEach.call(this,callback)
	}
}
var activeArea = function(id){

	map.querySelectorALL('.is-active').forEach(function(item){
		item.classList.remove('is-active')
	})
	document.querySelector('#List-'+id).classList.add('is-active')
	document.querySelector('#region-'+id).classList.add('is-active')

}
paths.forEach(function(path){
	path.addEventListener('mouseenter',function(e){
	var id = this.id.replace('region-','')
	activeArea(id)
	})

	})
links.forEach(function(link){
	link.addEventListener('mouseenter',function(){
		var id=this.id.replace('List-','')
		activeArea(id)
	})

})
