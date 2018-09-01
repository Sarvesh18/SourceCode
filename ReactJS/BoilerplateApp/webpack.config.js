var path = require('path');
var webpack = require('webpack');
var nodeExternals = require('webpack-node-externals');
var HtmlWebpackPlugin = require("html-webpack-plugin");
var MiniCssExtractPlugin = require("mini-css-extract-plugin");

var browserConfig = {
  mode: 'development',
  entry: './src/index.js',
  externals: [nodeExternals()],
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    //publicPath: '/'
  }, 
  devServer: {
    host: "localhost",
    inline: true,
    open: true,
    hot: true,
    port: 8080
  },
  module: {
    rules: [
      {  
        test: /\.(jsx|js)$/,
        //exclude: /node_modules/,
        use: 'babel-loader' 
      },
      {
        test: /\.css$/,
        loader: 'style-loader!css-loader?modules=true&localIdentName=[name]__[local]___[hash:base64:5]'
      },
      /*
      {
        test: /\.css$/,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
          },
          "css-loader"
      }
      */ 
      {
        test: /\.gif$/, 
        loader: 'url-loader'
      },
      {
        test: /\.(ttf|eot|svg)$/,
        loader: 'file-loader', 
      },
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./src/static/index.html",
      filename: "index.html"
    }),
    new MiniCssExtractPlugin({
      filename: "style.css",
      chunkFilename: "[id].css"
    }),
    new webpack.DefinePlugin({
      __isBrowser__: "true"
    })
  ]
}

module.exports = [browserConfig]