using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace TypeSort
{
    public sealed class Argument
    {
        public string Original { get; }
        public string Switch { get; private set; }
        public ReadOnlyCollection<string> SubArguments { get; }
        private List<string> subArguments;
        public Argument(string original)
        {
            Original = original;
            Switch = string.Empty;
            subArguments = new List<string>();
            SubArguments = new ReadOnlyCollection<string>(subArguments);
            Parse();
        }

        private void Parse()
        {
            if (string.IsNullOrEmpty(Original))
            {
                return;
            }
            char[] switchChars = { '/', '-' };
            if (!switchChars.Contains(Original[0]))
            {
                return;
            }
            string switchString = Original.Substring(1);
            string subArgsString = string.Empty;
            int colon = switchString.IndexOf(':');
            if (colon >= 0)
            {
                subArgsString = switchString.Substring(colon + 1);
                switchString = switchString.Substring(0, colon);
            }
            Switch = switchString;
            if (!string.IsNullOrEmpty(subArgsString))
                subArguments.AddRange(subArgsString.Split(';'));
        }

        public bool IsSimple => SubArguments.Count == 0;
        public bool IsSimpleSwitch => 
            !string.IsNullOrEmpty(Switch) && SubArguments.Count == 0;
        public bool IsCompoundSwitch =>
            !string.IsNullOrEmpty(Switch) && SubArguments.Count == 1;
        public bool IsCompleSwitch =>
            !string.IsNullOrEmpty(Switch) && SubArguments.Count > 0;
    }

    public sealed class ArgumentDefinition
    {
        public string ArgumentSwitch { get; }
        public string Syntax { get; }
        public string Description { get; }
        public Func<Argument, bool> Verifier { get; }
        public ArgumentDefinition(string argumentSwitch,
            string syntax, string description, Func<Argument, bool> verifier)
        {
            ArgumentSwitch = argumentSwitch;
            Syntax = syntax;
            Description = description;
            Verifier = verifier;
        }
        public bool Verify(Argument arg) => Verifier(arg);
    }

    public sealed class ArgumentSemanticAnalyser
    {
        private List<ArgumentDefinition> argumentDefinitions =
            new List<ArgumentDefinition>();
        private Dictionary<string, Action<Argument>> argumentActions =
            new Dictionary<string, Action<Argument>>();

        public ReadOnlyCollection<Argument> UnrecognizedArguments { get; private set; }
        public ReadOnlyCollection<Argument> MalformedArguments { get; private set; }
        public ReadOnlyCollection<Argument> RepeatedArguments { get; private set; }

        public
    }

    class CommandLineParsing
    {

    }
}
