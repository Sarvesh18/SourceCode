//var mongo = require('mongodb');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://localhost:27017/";

MongoClient.connect(url, function(err,db) {
    if(err) throw err;
    console.log('Database Created !');

    var dbo = db.db("TestDB");

    dbo.createCollection("Test1",function(err,res) {
        if(err) throw err;
        console.log("Collection Created !");
    })
    var myObj1 = { name: "Company Inc", address: "Highway 37" };
    dbo.collection("Test1").insertOne(myObj1, function(err,res) {
        if(err) throw err;
        console.log("1 document inserted");
    });

    var myobj2 = [
        { name: 'John', address: 'Highway 71'},
        { name: 'Peter', address: 'Lowstreet 4'},
        { name: 'Amy', address: 'Apple st 652'},
        { name: 'Hannah', address: 'Mountain 21'},
        { name: 'Michael', address: 'Valley 345'},
        { name: 'Sandy', address: 'Ocean blvd 2'},
        { name: 'Betty', address: 'Green Grass 1'},
        { name: 'Richard', address: 'Sky st 331'},
        { name: 'Susan', address: 'One way 98'},
        { name: 'Vicky', address: 'Yellow Garden 2'},
        { name: 'Ben', address: 'Park Lane 38'},
        { name: 'William', address: 'Central st 954'},
        { name: 'Chuck', address: 'Main Road 989'},
        { name: 'Viola', address: 'Sideway 1633'}
    ];
    dbo.collection("Test1").insertMany(myobj2,function(err,res) {
        if(err) throw err;
        console.log("many document inserted: "+res.insertedCount);
        console.log(res.result,"ok:1,n:14");
        console.log(res.ops,"name: address: _id:");
        console.log(res.insertedCount);
        console.log(res.insertedIds,'[]');
    });

    dbo.collection("Test1").findOne({},function(err,res) {
        if(err) throw err;
        console.log(res.name);
    });

    dbo.collection("Test1").find({},{_id: 0, name: 1}).toArray(function(err,res){
        if(err) throw err;
        console.log(res);
        //console.log(res[2].address);
    });

    var query = { address: /^S/ };
    dbo.collection("Test1").find(query).toArray(function(err, res) {
      if (err) throw err;
      console.log(res);
    });

    db.close();
});