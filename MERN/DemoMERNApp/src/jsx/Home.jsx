import React, { Component } from 'react';
import logo from '../static/logo.svg';
import style from '../style/style.css';

class Home extends Component {
    constructor(props) {
        super(props);
        console.log('Home props',props);
    }
    signOut() {
        console.log('signout()',this.props);
        this.props.onStatusChange(false);
        //this.props.history.push('/signout');
        //firebaseApp.auth().signOut();
    }
    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <img src={logo} className="App-logo" alt="logo" />
                    <h1 className="App-title">Welcome to React</h1>
                </header>
                <p className="App-intro">
                    To get started, edit <code>src/App.js</code> and save to reload.
                </p>
                {console.log('Home')}
                <h3>Welcome 
                {
                    //this.props.location.state.username
                } 
                !</h3><br/>
                <button type="button" className="btn btn-danger"
                    onClick={()=>this.signOut()}>Signout</button>
            </div>
        );
    }
}
    
    export default Home;