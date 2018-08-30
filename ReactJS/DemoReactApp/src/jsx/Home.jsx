import React from 'react';
import style from '../style/style.css';
import logo from '../static/logo.svg';
import icon from '../static/icon.png';
import Sign from './Sign.jsx';

import {testAction,thunkAction} from '../action';
import {connect} from 'react-redux';
import {bindActionCreators} from 'redux';

class Home extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            check1:'',
            check2:''
        };
        console.log('constructor()');
        console.log('props',props);
        console.log('state',this.state);
    }
    /*
    static getDerivedStateFromProps(props,state) {
        console.log('getDerivedStateFromProps()');
        console.log('props',props,'state',state);
        return null;
        //return {email: null};
    }
    */
    UNSAFE_componentWillMount() {
        console.log('UNSAFE_componentWillMount()');
    }
    componentDidMount() {
        console.log('componentDidMount()');
    }

    UNSAFE_componentWillReceiveProps(newProps) {
        console.log('UNSAFE_componentWillReceiveProps()',newProps);
    }
    shouldComponentUpdate(newProps, newState) {
        console.log('shouldComponentUpdate()',newProps,' ',newState);
        return true;
    }
    UNSAFE_componentWillUpdate(nextProps, nextState) {
        console.log('UNSAFE_componentWillUpdate()',nextProps,' ',nextState);
    }
    /*
    getSnapshotBeforeUpdate(prevProps, prevState) { 
        console.log('getSnapshotBeforeUpdate()',prevProps,' ',prevState);
    }
    */
    componentDidUpdate(prevProps, prevState) {
        console.log('componentDidUpdate()',prevProps,' ',prevState);
    }

    componentWillUnmount() {
        console.log('componentWillUnmount()');
    }
    componentDidCatch() {
        console.log('componentDidCatch()');
    }
   
    
    isUserLoggedIn() {
        console.log('isUserLoggedIn()');
        if(this.state.email!='')
        {
        return true;
        }
        else if(this.state.email=='') {
        return false;
        }
        else {
        return null;
        }
    }
    reduxTest() {
        console.log('props',this.props);
        console.log('state',this.state);
        this.props.thunkAction('okokokok');
        //this.props.dispatch(testAction('ssssssss'));
    }
    render() {
        console.log('render()');
        return(
            <div className="App">
                <header className="App-header">
                    <img src={logo} className="App-logo" alt="logo" />
                    <h1 className="App-title">Welcome to React</h1>
                </header>
                <p className="App-intro">
                    To get started, edit <code>src/App.js</code> and save to reload.
                </p>
                <img src={logo} className="App-logo" alt="logo" /> ReactJS
                <Sign />
                {/*
                <Switch>
                    <Route exact path="/" render={() => (
                        this.isUserLoggedIn() ? (
                                                    <Home />
                                                ) : (
                                                    <Redirect to="/signin" />
                                                )
                    )}/>

                    <Route exact path="/signin" render={() => (
                        this.isUserLoggedIn() ? (
                                                    <Redirect to="/" />
                                                ) : (
                                                    <Signin />
                                                )
                    )}/>

                    <Route exact path="/signup" render={() => (
                        this.isUserLoggedIn() ? (
                                                    <Redirect to="/" />
                                                ) : (
                                                    <Signup />
                                                )
                    )}/>
                </Switch>
                */}
                <button type="button" 
                    onClick={()=> {
                        this.reduxTest()
                    }}>Click Me
                </button>
                <footer>
                    <p className="App-intro">&copy; 2018. All Rights Reserved!</p>
                </footer>
            </div>
        )
    }
}

function mapStateToProps(state, ownProps) {
    console.log('mapStateToProps');
    console.log('state',state);
    return ({check1:state.test, 
        check2:state.thunkTest});
}
function mapDispatchToProps(dispatch, ownProps) {
    console.log('mapDispatchToProps');
    console.log('dispatch',dispatch);
    return bindActionCreators({testAction,thunkAction}, dispatch);
}

export default connect(mapStateToProps,mapDispatchToProps)(Home);
