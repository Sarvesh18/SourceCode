module.exports = {
    verbose: true,
    //"jest": {
    "setupTestFrameworkScriptFile": "<rootDir>src/config/setupTest.js",
    //}
    //"testEnvironment": "node"
    "moduleNameMapper": {
        "\\.(jpg|jpeg|png|gif|eot|otf|webp|svg|ttf|woff|woff2|mp4|webm|wav|mp3|m4a|aac|oga)$":"<rootDir>/__mocks__/fileMock.js",
        "\\.(css)$": "<rootDir>/__mocks__/styleMock.js"
    }
};