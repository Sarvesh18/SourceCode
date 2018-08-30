import React from "react";
import Loadable from 'react-loadable';

import Loading from './Loading.jsx';
//import Home from './Home';

const LoadableComponent = Loadable ({
    loader: () => import('./Home.jsx'),
    loading: Loading,
})

class App extends React.Component {
    render() {
        return <LoadableComponent/>
    }
}
export default App;

