/--- class / struct declare and define;
	{

		
		aggregate class
		consexpr class
		
	}

/--- constructor
	{
		/ --- synthesized constructor
		/ --- default constructor
		/ --- constructor initialize list
		/ --- default copy construct / default assignment constructor / default destructor
	}

/--- const
	{
		const menber function --- change the this property from type * const this to const type * const this
		const class_type : after constructor initialize, class_type object then get they const property,
							and only can call those const menber function

		mutable key word
		
		
		
	}

/--- friend
	a friend declare in a class just expain the access to this class for friend things is allowd,
	not a commonly declare, so, , it must declare outside the class 
	even the implementation of the friend thing in the class
	when call the friend function ( if the friend thing is a function )
	

/--- name lookup
	{
		compiler meet a name, check this name type declare before in current scope,
		if not find , go one outer scope till to the outest scope,
		if not find lastly, report error


		for class, compiler analysis all the declare name before member function body£¬
		so, when compiler in function body, all the name in this class can be see

	}

/--- explicit key word
	{
		forbid implicit convert
		explicit cast will allow implicit convert again, explicit key word become no used
		like: static_cast<Sales_data>(cin)
	}


/--- static 
	{

		
		menber function
			can't be decare with const
			
			
		menber variable		
		{						
			can be uncompeleted class
			can be class itself
			can be use for menber function parameter default argument

			
			belong the class not object, so it not initialized in constructor
			must be and only once time initialized 


			if static menber variable declare has in-class initial value,
			then must be define it outside class, except static const type / static constexpr type

		}
	}


