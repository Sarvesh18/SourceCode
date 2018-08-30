import React from 'react';
import style from '../style/style.css';
import logo from '../static/logo.svg';

class Loading extends React.Component {
    render() {
        return(
            <div className="loader" style={{textAlign: "center"}}>
            </div>
        )
    }
}

export default Loading;