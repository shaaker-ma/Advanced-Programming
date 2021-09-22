var jsonData = 
[
  {
    "id": 1,
    "name": "Sony Xperia Z3",
    "price": 899,
    "specs": {
      "manufacturer": "Sony",
      "storage": 16,
      "os": "Android",
      "camera": 15
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 2,
    "name": "Iphone 6",
    "price": 899,
    "specs": {
      "manufacturer": "Apple",
      "storage": 16,
      "os": "iOS",
      "camera": 8
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 3,
    "name": "HTC One M8",
    "price": 899,
    "specs": {
      "manufacturer": "HTC",
      "storage": 32,
      "os": "Android",
      "camera": 5
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 4,
    "name": "Galaxy Alpha",
    "price": 899,
    "specs": {
      "manufacturer": "Samsung",
      "storage": 32,
      "os": "Android",
      "camera": 12
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 5,
    "name": "Nokia Lumia",
    "price": 450,
    "specs": {
      "manufacturer": "Nokia",
      "storage": 16,
      "os": "Windows",
      "camera": 5
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 6,
    "name": "Zte Nubia",
    "price": 399,
    "specs": {
      "manufacturer": "ZTE",
      "storage": 32,
      "os": "Android",
      "camera": 12
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 7,
    "name": "Samsung Galaxy S5",
    "price": 399,
    "specs": {
      "manufacturer": "Samsung",
      "storage": 16,
      "os": "Android",
      "camera": 15
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 8,
    "name": "Iphone 5S",
    "price": 399,
    "specs": {
      "manufacturer": "Apple",
      "storage": 16,
      "os": "iOS",
      "camera": 8
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 4,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  },
  {
    "id": 9,
    "name": "OnePlus One",
    "price": 300,
    "specs": {
      "manufacturer": "OnePlus",
      "storage": 64,
      "os": "Android",
      "camera": 13
    },
    "description": "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam tristique ipsum in efficitur pharetra. Maecenas luctus ante in neque maximus, sed viverra sem posuere. Vestibulum lectus nisi, laoreet vel suscipit nec, feugiat at odio. Etiam eget tellus arcu.",
    "rating": 10,
    "image": {
      "small": "http://placehold.it/328x600",
      "large": "http://placehold.it/700x250"
    }
  }
];

$(function () {
	var products = [],

		filters = {};
	var checkboxes = $('.all-products input[type=checkbox]');

	checkboxes.click(function () {

		var that = $(this),
			specName = that.attr('name');

		if(that.is(":checked")) {

			if(!(filters[specName] && filters[specName].length)){
				filters[specName] = [];
			}

			filters[specName].push(that.val());

			createQueryHash(filters);

		}
		if(!that.is(":checked")) {

			if(filters[specName] && filters[specName].length && (filters[specName].indexOf(that.val()) != -1)){

				var index = filters[specName].indexOf(that.val());

				filters[specName].splice(index, 1);

				if(!filters[specName].length){
					delete filters[specName];
				}

			}

			createQueryHash(filters);
		}
	});

	$('.filters button').click(function (e) {
		e.preventDefault();
		window.location.hash = '#';
	});



	var singleProductPage = $('.single-product');

	singleProductPage.on('click', function (e) {

		if (singleProductPage.hasClass('visible')) {

			var clicked = $(e.target);

			if (clicked.hasClass('close') || clicked.hasClass('overlay')) {
				createQueryHash(filters);
			}

		}

	});

	$(window).on('hashchange', function(){
		render(window.location.hash);
	});

	function render(url) {

		var temp = url.split('/')[0];

		$('.main-content .page').removeClass('visible');


		var	map = {

			'': function() {

				filters = {};
				checkboxes.prop('checked',false);

				renderProductsPage(products);
			},

			'#product': function() {

				var index = url.split('#product/')[1].trim();

				renderSingleProductPage(index, products);
			},

			'#filter': function() {

				url = url.split('#filter/')[1].trim();

				try {
					filters = JSON.parse(url);
				}
				catch(err) {
					window.location.hash = '#';
					return;
				}

				renderFilterResults(filters, products);
			}

		};

		if(map[temp]){
			map[temp]();
		}
		else {
			renderErrorPage();
		}

	}

	function generateAllProductsHTML(data){

		var list = $('.all-products .products-list');

		var theTemplateScript = $("#products-template").html();
		var theTemplate = Handlebars.compile (theTemplateScript);
		list.append (theTemplate(data));


		list.find('li').on('click', function (e) {
			e.preventDefault();

			var productIndex = $(this).data('index');

			window.location.hash = 'product/' + productIndex;
		})
	}

	function renderProductsPage(data){

		var page = $('.all-products'),
			allProducts = $('.all-products .products-list > li');

		allProducts.addClass('hidden');

		allProducts.each(function () {

			var that = $(this);

			data.forEach(function (item) {
				if(that.data('index') == item.id){
					that.removeClass('hidden');
				}
			});
		});

		page.addClass('visible');

	}


	function renderSingleProductPage(index, data){

		var page = $('.single-product'),
			container = $('.preview-large');

		if(data.length){
			data.forEach(function (item) {
				if(item.id == index){
					container.find('h3').text(item.name);
					container.find('img').attr('src', item.image.large);
					container.find('p').text(item.description);
				}
			});
		}

		page.addClass('visible');

	}

	function renderFilterResults(filters, products){

		var criteria = ['manufacturer','storage','os','camera'],
			results = [],
			isFiltered = false;

		checkboxes.prop('checked', false);


		criteria.forEach(function (c) {

			if(filters[c] && filters[c].length){

				if(isFiltered){
					products = results;
					results = [];
				}

				filters[c].forEach(function (filter) {

					products.forEach(function (item){

						if(typeof item.specs[c] == 'number'){
							if(item.specs[c] == filter){
								results.push(item);
								isFiltered = true;
							}
						}

						if(typeof item.specs[c] == 'string'){
							if(item.specs[c].toLowerCase().indexOf(filter) != -1){
								results.push(item);
								isFiltered = true;
							}
						}

					});

					if(c && filter){
						$('input[name='+c+'][value='+filter+']').prop('checked',true);
					}
				});
			}

		});
		renderProductsPage(results);
	}


	function renderErrorPage(){
		var page = $('.error');
		page.addClass('visible');
	}

	function createQueryHash(filters){

		if(!$.isEmptyObject(filters)){
			window.location.hash = '#filter/' + JSON.stringify(filters);
		}
		else{
			window.location.hash = '#';
		}

	}
  
    products = jsonData;
    generateAllProductsHTML(jsonData);
    $(window).trigger('hashchange');

});